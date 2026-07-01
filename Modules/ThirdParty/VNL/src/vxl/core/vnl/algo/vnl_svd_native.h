// vnl_svd_native.h - native C++ LINPACK xsvdc engine (all 4 precisions),
// a byte-exact drop-in for v3p_netlib_{s,d,c,z}svdc_ that reuses the retained
// v3p netlib BLAS. Overly conservative on purpose: it reproduces LINPACK
// bit-for-bit (under -ffp-contract=off) so no baselines move. See
// vnl_svd.hxx for the dispatch. Provenance/validation: ITK .devlocal
// svdc-byte-harness (72/72 cases 0-ULP).
// Native C++ port of LINPACK xsvdc, transcribed 1:1 from the vendored Fortran
// (v3p/netlib/linpack/{s,d}svdc.f for real; {c,z}svdc.f for complex). Reuses the
// RETAINED netlib BLAS primitives so the only floating-point ops are (a) inside
// byte-identical BLAS and (b) the handful of scalar ops copied verbatim — giving
// 0-ULP agreement with the vendored engine (the #6473 QR approach).
//
// Fortran is 1-based column-major. The port keeps 1-based indexing via A()/ADDR()
// so the transcription stays line-for-line checkable against the .f source; a
// later cleanup pass can lower to idiomatic 0-based C++ once the diff is empty.
//
// Real path (native_svdc<float|double>): the f2c reference promotes single-
// precision BLAS returns (snrm2/sdot) to double and truncates at assignment to
// `real` locals. The template reproduces this by (1) nrm2/dot wrappers that
// return double, (2) T-typed literals, (3) sqrt routed through double. For
// T=double these are identities, so the same template is byte-exact at both
// precisions.
#ifndef vnl_svd_native_h_
#define vnl_svd_native_h_

#include <cmath>
#include <complex>
#include <vnl/algo/vnl_netlib.h> // v3p_netlib_* BLAS symbols

// Byte-exactness vs the f2c reference requires no FMA contraction: f2c's explicit
// q__1.r=a*b temporaries and std::complex operators fuse a*b-c*d differently, so
// with default contraction the complex paths drift 1-4 ULP. Pinning it off also
// makes the engine platform-deterministic (FMA availability varies x86/ARM). The
// pragma is honored by clang; builds should also pass -ffp-contract=off for GCC.
#if defined(__clang__)
#  pragma STDC FP_CONTRACT OFF
#endif


namespace svdc_native_detail
{
// 1-based column-major element access / address, matching Fortran x(i,j).
template <class T>
inline T &
A(T * base, long ld, long i, long j)
{
  return base[(j - 1) * ld + (i - 1)];
}
template <class T>
inline T *
ADDR(T * base, long ld, long i, long j)
{
  return base + (j - 1) * ld + (i - 1);
}

// ---- real BLAS dispatch (nrm2/dot return double per f2c) ----
inline double
blas_nrm2(long n, float * x, long incx)
{
  return v3p_netlib_snrm2_(&n, x, &incx);
}
inline double
blas_nrm2(long n, double * x, long incx)
{
  return v3p_netlib_dnrm2_(&n, x, &incx);
}
inline double
blas_dot(long n, float * x, long ix, float * y, long iy)
{
  return v3p_netlib_sdot_(&n, x, &ix, y, &iy);
}
inline double
blas_dot(long n, double * x, long ix, double * y, long iy)
{
  return v3p_netlib_ddot_(&n, x, &ix, y, &iy);
}
inline void
blas_scal(long n, float a, float * x, long incx)
{
  v3p_netlib_sscal_(&n, &a, x, &incx);
}
inline void
blas_scal(long n, double a, double * x, long incx)
{
  v3p_netlib_dscal_(&n, &a, x, &incx);
}
inline void
blas_axpy(long n, float a, float * x, long ix, float * y, long iy)
{
  v3p_netlib_saxpy_(&n, &a, x, &ix, y, &iy);
}
inline void
blas_axpy(long n, double a, double * x, long ix, double * y, long iy)
{
  v3p_netlib_daxpy_(&n, &a, x, &ix, y, &iy);
}
inline void
blas_rot(long n, float * x, long ix, float * y, long iy, float c, float s)
{
  v3p_netlib_srot_(&n, x, &ix, y, &iy, &c, &s);
}
inline void
blas_rot(long n, double * x, long ix, double * y, long iy, double c, double s)
{
  v3p_netlib_drot_(&n, x, &ix, y, &iy, &c, &s);
}
inline void
blas_rotg(float & a, float & b, float & c, float & s)
{
  v3p_netlib_srotg_(&a, &b, &c, &s);
}
inline void
blas_rotg(double & a, double & b, double & c, double & s)
{
  v3p_netlib_drotg_(&a, &b, &c, &s);
}
inline void
blas_swap(long n, float * x, long ix, float * y, long iy)
{
  v3p_netlib_sswap_(&n, x, &ix, y, &iy);
}
inline void
blas_swap(long n, double * x, long ix, double * y, long iy)
{
  v3p_netlib_dswap_(&n, x, &ix, y, &iy);
}

// sign(a,b): |a| with the sign of b (Fortran DSIGN/R_SIGN).
template <class T>
inline T
fsign(T a, T b)
{
  const T m = std::abs(a);
  return b >= T(0) ? m : -m;
}
// sqrt routed through double then truncated to T (matches f2c sqrt(doublereal)).
template <class T>
inline T
fsqrt(T x)
{
  return T(std::sqrt(double(x)));
}

// ---- complex scalar helpers matching libf2c exactly (byte-exactness) ----
// f__cabs: scaled magnitude computed in double (backs both c_abs and z_abs).
inline double
f2c_cabs(double re, double im)
{
  if (re < 0)
    re = -re;
  if (im < 0)
    im = -im;
  if (im > re)
  {
    const double t = re;
    re = im;
    im = t;
  }
  if ((re + im) == re)
    return re;
  const double q = im / re;
  return re * std::sqrt(1.0 + q * q);
}
template <class R>
inline R
cabsm(std::complex<R> z) // |z| via f__cabs (double math, R-truncated)
{
  return R(f2c_cabs(double(z.real()), double(z.imag())));
}
// c_div / z_div: Smith's algorithm in double, result stored to R (truncates for
// float, exact for double) — reproduces libf2c c_div (float) and z_div (double).
template <class R>
inline std::complex<R>
f2c_cdiv(std::complex<R> a, std::complex<R> b)
{
  double ar = a.real(), ai = a.imag(), br = b.real(), bi = b.imag();
  double abr = br < 0 ? -br : br;
  double abi = bi < 0 ? -bi : bi;
  double ratio, den, cr, ci;
  if (abr <= abi)
  {
    ratio = br / bi;
    den = bi * (1.0 + ratio * ratio);
    cr = (ar * ratio + ai) / den;
    ci = (ai * ratio - ar) / den;
  }
  else
  {
    ratio = bi / br;
    den = br * (1.0 + ratio * ratio);
    cr = (ar + ai * ratio) / den;
    ci = (ai - ar * ratio) / den;
  }
  return std::complex<R>(R(cr), R(ci));
}
// cabs1(z) = |Re(z)| + |Im(z)| (the LINPACK negligibility test for bidiag).
template <class R>
inline R
cabs1(std::complex<R> z)
{
  return std::abs(z.real()) + std::abs(z.imag());
}
// csign(z1,z2) = |z1| * (z2/|z2|), expanded exactly as f2c (R-truncated cabs).
template <class R>
inline std::complex<R>
csign(std::complex<R> z1, std::complex<R> z2)
{
  const R r3 = cabsm(z1);
  const R r4 = cabsm(z2);
  return std::complex<R>(r3 * (z2.real() / r4), r3 * (z2.imag() / r4));
}

// ---- complex BLAS dispatch ----
inline double
blas_cnrm2(long n, std::complex<float> * x, long incx)
{
  return v3p_netlib_scnrm2_(&n, x, &incx);
}
inline double
blas_cnrm2(long n, std::complex<double> * x, long incx)
{
  return v3p_netlib_dznrm2_(&n, x, &incx);
}
inline void
blas_cscal(long n, std::complex<float> a, std::complex<float> * x, long incx)
{
  v3p_netlib_cscal_(&n, &a, x, &incx);
}
inline void
blas_cscal(long n, std::complex<double> a, std::complex<double> * x, long incx)
{
  v3p_netlib_zscal_(&n, &a, x, &incx);
}
inline std::complex<float>
blas_dotc(long n, std::complex<float> * x, long ix, std::complex<float> * y, long iy)
{
  std::complex<float> ret;
  v3p_netlib_cdotc_(&ret, &n, x, &ix, y, &iy);
  return ret;
}
inline std::complex<double>
blas_dotc(long n, std::complex<double> * x, long ix, std::complex<double> * y, long iy)
{
  std::complex<double> ret;
  v3p_netlib_zdotc_(&ret, &n, x, &ix, y, &iy);
  return ret;
}
inline void
blas_caxpy(long n, std::complex<float> a, std::complex<float> * x, long ix, std::complex<float> * y, long iy)
{
  v3p_netlib_caxpy_(&n, &a, x, &ix, y, &iy);
}
inline void
blas_caxpy(long n, std::complex<double> a, std::complex<double> * x, long ix, std::complex<double> * y, long iy)
{
  v3p_netlib_zaxpy_(&n, &a, x, &ix, y, &iy);
}
inline void
blas_csrot(long n, std::complex<float> * x, long ix, std::complex<float> * y, long iy, float c, float s)
{
  v3p_netlib_csrot_(&n, x, &ix, y, &iy, &c, &s);
}
inline void
blas_csrot(long n, std::complex<double> * x, long ix, std::complex<double> * y, long iy, double c, double s)
{
  v3p_netlib_zdrot_(&n, x, &ix, y, &iy, &c, &s);
}
inline void
blas_cswap(long n, std::complex<float> * x, long ix, std::complex<float> * y, long iy)
{
  v3p_netlib_cswap_(&n, x, &ix, y, &iy);
}
inline void
blas_cswap(long n, std::complex<double> * x, long ix, std::complex<double> * y, long iy)
{
  v3p_netlib_zswap_(&n, x, &ix, y, &iy);
}
} // namespace svdc_native_detail

// Real templated port. Signature mirrors v3p_netlib_{s,d}svdc_ (LINPACK order).
template <class T>
inline int
native_svdc(T * x, long const * ldx_, long const * n_, long const * p_, T * s, T * e, T * u, long const * ldu_, T * v,
            long const * ldv_, T * work, long const * job_, long * info)
{
  using namespace svdc_native_detail;
  const long ldx = *ldx_, n = *n_, p = *p_, ldu = *ldu_, ldv = *ldv_, job = *job_;

  long i, iter, j, jobu, k, kase, kk, l, ll, lls, lm1, lp1, ls, lu, m, maxit, mm, mm1, mp1, nct, nctp1, ncu, nrt, nrtp1;
  T    t, b, c, cs, el, emm1, f, g, scale, shift, sl, sm, sn, smm1, t1, test, ztest;
  bool wantu, wantv;
  long one = 1;

  maxit = 1000;

  wantu = false;
  wantv = false;
  jobu = (job % 100) / 10;
  ncu = n;
  if (jobu > 1)
    ncu = (n < p ? n : p);
  if (jobu != 0)
    wantu = true;
  if (job % 10 != 0)
    wantv = true;

  *info = 0;
  nct = (n - 1 < p ? n - 1 : p);
  nrt = 0;
  {
    const long t2 = (p - 2 < n ? p - 2 : n);
    if (t2 > nrt)
      nrt = t2;
  }
  lu = (nct > nrt ? nct : nrt);
  if (lu >= 1)
  {
    for (l = 1; l <= lu; ++l)
    {
      lp1 = l + 1;
      if (l <= nct)
      {
        long len = n - l + 1;
        s[l - 1] = blas_nrm2(len, ADDR(x, ldx, l, l), one);
        if (s[l - 1] != T(0))
        {
          if (A(x, ldx, l, l) != T(0))
            s[l - 1] = fsign(s[l - 1], A(x, ldx, l, l));
          T inv = T(1) / s[l - 1];
          blas_scal(len, inv, ADDR(x, ldx, l, l), one);
          A(x, ldx, l, l) = T(1) + A(x, ldx, l, l);
        }
        s[l - 1] = -s[l - 1];
      }
      if (p >= lp1)
      {
        for (j = lp1; j <= p; ++j)
        {
          if (l <= nct && s[l - 1] != T(0))
          {
            long len = n - l + 1;
            t = -blas_dot(len, ADDR(x, ldx, l, l), one, ADDR(x, ldx, l, j), one) / A(x, ldx, l, l);
            blas_axpy(len, t, ADDR(x, ldx, l, l), one, ADDR(x, ldx, l, j), one);
          }
          e[j - 1] = A(x, ldx, l, j);
        }
      }
      if (wantu && l <= nct)
      {
        for (i = l; i <= n; ++i)
          A(u, ldu, i, l) = A(x, ldx, i, l);
      }
      if (l <= nrt)
      {
        long len = p - l;
        e[l - 1] = blas_nrm2(len, &e[lp1 - 1], one);
        if (e[l - 1] != T(0))
        {
          if (e[lp1 - 1] != T(0))
            e[l - 1] = fsign(e[l - 1], e[lp1 - 1]);
          T inv = T(1) / e[l - 1];
          blas_scal(len, inv, &e[lp1 - 1], one);
          e[lp1 - 1] = T(1) + e[lp1 - 1];
        }
        e[l - 1] = -e[l - 1];
        if (lp1 <= n && e[l - 1] != T(0))
        {
          for (i = lp1; i <= n; ++i)
            work[i - 1] = T(0);
          long len2 = n - l;
          for (j = lp1; j <= p; ++j)
            blas_axpy(len2, e[j - 1], ADDR(x, ldx, lp1, j), one, &work[lp1 - 1], one);
          for (j = lp1; j <= p; ++j)
          {
            T coef = -e[j - 1] / e[lp1 - 1];
            blas_axpy(len2, coef, &work[lp1 - 1], one, ADDR(x, ldx, lp1, j), one);
          }
        }
        if (wantv)
        {
          for (i = lp1; i <= p; ++i)
            A(v, ldv, i, l) = e[i - 1];
        }
      }
    }
  }

  m = (p < n + 1 ? p : n + 1);
  nctp1 = nct + 1;
  nrtp1 = nrt + 1;
  if (nct < p)
    s[nctp1 - 1] = A(x, ldx, nctp1, nctp1);
  if (n < m)
    s[m - 1] = T(0);
  if (nrtp1 < m)
    e[nrtp1 - 1] = A(x, ldx, nrtp1, m);
  e[m - 1] = T(0);

  if (wantu)
  {
    if (ncu >= nctp1)
    {
      for (j = nctp1; j <= ncu; ++j)
      {
        for (i = 1; i <= n; ++i)
          A(u, ldu, i, j) = T(0);
        A(u, ldu, j, j) = T(1);
      }
    }
    if (nct >= 1)
    {
      for (ll = 1; ll <= nct; ++ll)
      {
        l = nct - ll + 1;
        if (s[l - 1] != T(0))
        {
          lp1 = l + 1;
          if (ncu >= lp1)
          {
            for (j = lp1; j <= ncu; ++j)
            {
              long len = n - l + 1;
              t = -blas_dot(len, ADDR(u, ldu, l, l), one, ADDR(u, ldu, l, j), one) / A(u, ldu, l, l);
              blas_axpy(len, t, ADDR(u, ldu, l, l), one, ADDR(u, ldu, l, j), one);
            }
          }
          long len = n - l + 1;
          blas_scal(len, T(-1), ADDR(u, ldu, l, l), one);
          A(u, ldu, l, l) = T(1) + A(u, ldu, l, l);
          lm1 = l - 1;
          if (lm1 >= 1)
            for (i = 1; i <= lm1; ++i)
              A(u, ldu, i, l) = T(0);
        }
        else
        {
          for (i = 1; i <= n; ++i)
            A(u, ldu, i, l) = T(0);
          A(u, ldu, l, l) = T(1);
        }
      }
    }
  }

  if (wantv)
  {
    for (ll = 1; ll <= p; ++ll)
    {
      l = p - ll + 1;
      lp1 = l + 1;
      if (l <= nrt && e[l - 1] != T(0))
      {
        for (j = lp1; j <= p; ++j)
        {
          long len = p - l;
          t = -blas_dot(len, ADDR(v, ldv, lp1, l), one, ADDR(v, ldv, lp1, j), one) / A(v, ldv, lp1, l);
          blas_axpy(len, t, ADDR(v, ldv, lp1, l), one, ADDR(v, ldv, lp1, j), one);
        }
      }
      for (i = 1; i <= p; ++i)
        A(v, ldv, i, l) = T(0);
      A(v, ldv, l, l) = T(1);
    }
  }

  mm = m;
  iter = 0;
  while (true)
  {
    if (m == 0)
      break;
    if (iter >= maxit)
    {
      *info = m;
      break;
    }

    for (ll = 1; ll <= m; ++ll)
    {
      l = m - ll;
      if (l == 0)
        break;
      test = std::abs(s[l - 1]) + std::abs(s[l + 1 - 1]);
      ztest = test + std::abs(e[l - 1]);
      if (ztest == test)
      {
        e[l - 1] = T(0);
        break;
      }
    }
    if (l == m - 1)
    {
      kase = 4;
    }
    else
    {
      lp1 = l + 1;
      mp1 = m + 1;
      for (lls = lp1; lls <= mp1; ++lls)
      {
        ls = m - lls + lp1;
        if (ls == l)
          break;
        test = T(0);
        if (ls != m)
          test = test + std::abs(e[ls - 1]);
        if (ls != l + 1)
          test = test + std::abs(e[ls - 1 - 1]);
        ztest = test + std::abs(s[ls - 1]);
        if (ztest == test)
        {
          s[ls - 1] = T(0);
          break;
        }
      }
      if (ls == l)
      {
        kase = 3;
      }
      else if (ls == m)
      {
        kase = 1;
      }
      else
      {
        kase = 2;
        l = ls;
      }
    }
    l = l + 1;

    switch (kase)
    {
      case 1:
      {
        mm1 = m - 1;
        f = e[m - 1 - 1];
        e[m - 1 - 1] = T(0);
        for (kk = l; kk <= mm1; ++kk)
        {
          k = mm1 - kk + l;
          t1 = s[k - 1];
          blas_rotg(t1, f, cs, sn);
          s[k - 1] = t1;
          if (k != l)
          {
            f = -sn * e[k - 1 - 1];
            e[k - 1 - 1] = cs * e[k - 1 - 1];
          }
          if (wantv)
            blas_rot(p, ADDR(v, ldv, 1, k), one, ADDR(v, ldv, 1, m), one, cs, sn);
        }
        break;
      }
      case 2:
      {
        f = e[l - 1 - 1];
        e[l - 1 - 1] = T(0);
        for (k = l; k <= m; ++k)
        {
          t1 = s[k - 1];
          blas_rotg(t1, f, cs, sn);
          s[k - 1] = t1;
          f = -sn * e[k - 1];
          e[k - 1] = cs * e[k - 1];
          if (wantu)
            blas_rot(n, ADDR(u, ldu, 1, k), one, ADDR(u, ldu, 1, l - 1), one, cs, sn);
        }
        break;
      }
      case 3:
      {
        {
          T a1 = std::abs(s[m - 1]), a2 = std::abs(s[m - 1 - 1]), a3 = std::abs(e[m - 1 - 1]), a4 = std::abs(s[l - 1]),
            a5 = std::abs(e[l - 1]);
          scale = a1;
          if (a2 > scale)
            scale = a2;
          if (a3 > scale)
            scale = a3;
          if (a4 > scale)
            scale = a4;
          if (a5 > scale)
            scale = a5;
        }
        sm = s[m - 1] / scale;
        smm1 = s[m - 1 - 1] / scale;
        emm1 = e[m - 1 - 1] / scale;
        sl = s[l - 1] / scale;
        el = e[l - 1] / scale;
        b = ((smm1 + sm) * (smm1 - sm) + emm1 * emm1) / T(2);
        c = (sm * emm1) * (sm * emm1);
        shift = T(0);
        if (b != T(0) || c != T(0))
        {
          shift = fsqrt(b * b + c);
          if (b < T(0))
            shift = -shift;
          shift = c / (b + shift);
        }
        f = (sl + sm) * (sl - sm) + shift;
        g = sl * el;
        mm1 = m - 1;
        for (k = l; k <= mm1; ++k)
        {
          blas_rotg(f, g, cs, sn);
          if (k != l)
            e[k - 1 - 1] = f;
          f = cs * s[k - 1] + sn * e[k - 1];
          e[k - 1] = cs * e[k - 1] - sn * s[k - 1];
          g = sn * s[k + 1 - 1];
          s[k + 1 - 1] = cs * s[k + 1 - 1];
          if (wantv)
            blas_rot(p, ADDR(v, ldv, 1, k), one, ADDR(v, ldv, 1, k + 1), one, cs, sn);
          blas_rotg(f, g, cs, sn);
          s[k - 1] = f;
          f = cs * e[k - 1] + sn * s[k + 1 - 1];
          s[k + 1 - 1] = -sn * e[k - 1] + cs * s[k + 1 - 1];
          g = sn * e[k + 1 - 1];
          e[k + 1 - 1] = cs * e[k + 1 - 1];
          if (wantu && k < n)
            blas_rot(n, ADDR(u, ldu, 1, k), one, ADDR(u, ldu, 1, k + 1), one, cs, sn);
        }
        e[m - 1 - 1] = f;
        iter = iter + 1;
        break;
      }
      case 4:
      {
        if (s[l - 1] < T(0))
        {
          s[l - 1] = -s[l - 1];
          if (wantv)
            blas_scal(p, T(-1), ADDR(v, ldv, 1, l), one);
        }
        while (l != mm)
        {
          if (s[l - 1] >= s[l + 1 - 1])
            break;
          t = s[l - 1];
          s[l - 1] = s[l + 1 - 1];
          s[l + 1 - 1] = t;
          if (wantv && l < p)
            blas_swap(p, ADDR(v, ldv, 1, l), one, ADDR(v, ldv, 1, l + 1), one);
          if (wantu && l < n)
            blas_swap(n, ADDR(u, ldu, 1, l), one, ADDR(u, ldu, 1, l + 1), one);
          l = l + 1;
        }
        iter = 0;
        m = m - 1;
        break;
      }
    }
  }
  return 0;
}

// Complex templated port (R = float -> csvdc; R = double -> zsvdc), transcribed
// 1:1 from {c,z}svdc.f. Uses BLAS + libf2c-faithful c_div/c_abs for byte-exact
// scalar ops; std::complex operators only for +,-,*,conj (which match f2c inline
// expansion). Real work variables are R; complex work variables are complex<R>.
template <class R>
inline int
native_csvdc_tmpl(std::complex<R> * x, long const * ldx_, long const * n_, long const * p_, std::complex<R> * s,
                  std::complex<R> * e, std::complex<R> * u, long const * ldu_, std::complex<R> * v, long const * ldv_,
                  std::complex<R> * work, long const * job_, long * info)
{
  using namespace svdc_native_detail;
  using S = std::complex<R>;
  const long ldx = *ldx_, n = *n_, p = *p_, ldu = *ldu_, ldv = *ldv_, job = *job_;

  long i, iter, j, jobu, k, kase, kk, l, ll, lls, lm1, lp1, ls, lu, m, maxit, mm, mm1, mp1, nct, nctp1, ncu, nrt, nrtp1;
  S    t;
  R    b, c, cs, el, emm1, f, g, scale, shift, sl, sm, sn, smm1, t1, test, ztest;
  bool wantu, wantv;
  long one = 1;

  maxit = 1000;
  wantu = false;
  wantv = false;
  jobu = (job % 100) / 10;
  ncu = n;
  if (jobu > 1)
    ncu = (n < p ? n : p);
  if (jobu != 0)
    wantu = true;
  if (job % 10 != 0)
    wantv = true;

  *info = 0;
  nct = (n - 1 < p ? n - 1 : p);
  nrt = 0;
  {
    const long t2 = (p - 2 < n ? p - 2 : n);
    if (t2 > nrt)
      nrt = t2;
  }
  lu = (nct > nrt ? nct : nrt);
  if (lu >= 1)
  {
    for (l = 1; l <= lu; ++l)
    {
      lp1 = l + 1;
      if (l <= nct)
      {
        long len = n - l + 1;
        s[l - 1] = S(R(blas_cnrm2(len, ADDR(x, ldx, l, l), one)), R(0));
        if (cabs1(s[l - 1]) != R(0))
        {
          if (cabs1(A(x, ldx, l, l)) != R(0))
            s[l - 1] = csign(s[l - 1], A(x, ldx, l, l));
          S inv = f2c_cdiv(S(R(1)), s[l - 1]);
          blas_cscal(len, inv, ADDR(x, ldx, l, l), one);
          A(x, ldx, l, l) = S(R(1)) + A(x, ldx, l, l);
        }
        s[l - 1] = -s[l - 1];
      }
      if (p >= lp1)
      {
        for (j = lp1; j <= p; ++j)
        {
          if (l <= nct && cabs1(s[l - 1]) != R(0))
          {
            long len = n - l + 1;
            S    dc = blas_dotc(len, ADDR(x, ldx, l, l), one, ADDR(x, ldx, l, j), one);
            t = f2c_cdiv(-dc, A(x, ldx, l, l));
            blas_caxpy(len, t, ADDR(x, ldx, l, l), one, ADDR(x, ldx, l, j), one);
          }
          e[j - 1] = std::conj(A(x, ldx, l, j));
        }
      }
      if (wantu && l <= nct)
      {
        for (i = l; i <= n; ++i)
          A(u, ldu, i, l) = A(x, ldx, i, l);
      }
      if (l <= nrt)
      {
        long len = p - l;
        e[l - 1] = S(R(blas_cnrm2(len, &e[lp1 - 1], one)), R(0));
        if (cabs1(e[l - 1]) != R(0))
        {
          if (cabs1(e[lp1 - 1]) != R(0))
            e[l - 1] = csign(e[l - 1], e[lp1 - 1]);
          S inv = f2c_cdiv(S(R(1)), e[l - 1]);
          blas_cscal(len, inv, &e[lp1 - 1], one);
          e[lp1 - 1] = S(R(1)) + e[lp1 - 1];
        }
        e[l - 1] = -std::conj(e[l - 1]);
        if (lp1 <= n && cabs1(e[l - 1]) != R(0))
        {
          for (i = lp1; i <= n; ++i)
            work[i - 1] = S(0);
          long len2 = n - l;
          for (j = lp1; j <= p; ++j)
            blas_caxpy(len2, e[j - 1], ADDR(x, ldx, lp1, j), one, &work[lp1 - 1], one);
          for (j = lp1; j <= p; ++j)
          {
            S coef = std::conj(f2c_cdiv(-e[j - 1], e[lp1 - 1]));
            blas_caxpy(len2, coef, &work[lp1 - 1], one, ADDR(x, ldx, lp1, j), one);
          }
        }
        if (wantv)
        {
          for (i = lp1; i <= p; ++i)
            A(v, ldv, i, l) = e[i - 1];
        }
      }
    }
  }

  m = (p < n + 1 ? p : n + 1);
  nctp1 = nct + 1;
  nrtp1 = nrt + 1;
  if (nct < p)
    s[nctp1 - 1] = A(x, ldx, nctp1, nctp1);
  if (n < m)
    s[m - 1] = S(0);
  if (nrtp1 < m)
    e[nrtp1 - 1] = A(x, ldx, nrtp1, m);
  e[m - 1] = S(0);

  if (wantu)
  {
    if (ncu >= nctp1)
    {
      for (j = nctp1; j <= ncu; ++j)
      {
        for (i = 1; i <= n; ++i)
          A(u, ldu, i, j) = S(0);
        A(u, ldu, j, j) = S(R(1));
      }
    }
    if (nct >= 1)
    {
      for (ll = 1; ll <= nct; ++ll)
      {
        l = nct - ll + 1;
        if (cabs1(s[l - 1]) != R(0))
        {
          lp1 = l + 1;
          if (ncu >= lp1)
          {
            for (j = lp1; j <= ncu; ++j)
            {
              long len = n - l + 1;
              S    dc = blas_dotc(len, ADDR(u, ldu, l, l), one, ADDR(u, ldu, l, j), one);
              t = f2c_cdiv(-dc, A(u, ldu, l, l));
              blas_caxpy(len, t, ADDR(u, ldu, l, l), one, ADDR(u, ldu, l, j), one);
            }
          }
          long len = n - l + 1;
          blas_cscal(len, S(R(-1)), ADDR(u, ldu, l, l), one);
          A(u, ldu, l, l) = S(R(1)) + A(u, ldu, l, l);
          lm1 = l - 1;
          if (lm1 >= 1)
            for (i = 1; i <= lm1; ++i)
              A(u, ldu, i, l) = S(0);
        }
        else
        {
          for (i = 1; i <= n; ++i)
            A(u, ldu, i, l) = S(0);
          A(u, ldu, l, l) = S(R(1));
        }
      }
    }
  }

  if (wantv)
  {
    for (ll = 1; ll <= p; ++ll)
    {
      l = p - ll + 1;
      lp1 = l + 1;
      if (l <= nrt && cabs1(e[l - 1]) != R(0))
      {
        for (j = lp1; j <= p; ++j)
        {
          long len = p - l;
          S    dc = blas_dotc(len, ADDR(v, ldv, lp1, l), one, ADDR(v, ldv, lp1, j), one);
          t = f2c_cdiv(-dc, A(v, ldv, lp1, l));
          blas_caxpy(len, t, ADDR(v, ldv, lp1, l), one, ADDR(v, ldv, lp1, j), one);
        }
      }
      for (i = 1; i <= p; ++i)
        A(v, ldv, i, l) = S(0);
      A(v, ldv, l, l) = S(R(1));
    }
  }

  // transform s and e so that they are real
  for (i = 1; i <= m; ++i)
  {
    if (cabs1(s[i - 1]) != R(0))
    {
      t = S(cabsm(s[i - 1]), R(0));
      S r = f2c_cdiv(s[i - 1], t);
      s[i - 1] = t;
      if (i < m)
        e[i - 1] = f2c_cdiv(e[i - 1], r);
      if (wantu)
        blas_cscal(n, r, ADDR(u, ldu, 1, i), one);
    }
    if (i == m)
      break;
    if (cabs1(e[i - 1]) != R(0))
    {
      t = S(cabsm(e[i - 1]), R(0));
      S r = f2c_cdiv(t, e[i - 1]);
      e[i - 1] = t;
      s[i + 1 - 1] = s[i + 1 - 1] * r;
      if (wantv)
        blas_cscal(p, r, ADDR(v, ldv, 1, i + 1), one);
    }
  }

  mm = m;
  iter = 0;
  while (true)
  {
    if (m == 0)
      break;
    if (iter >= maxit)
    {
      *info = m;
      break;
    }

    for (ll = 1; ll <= m; ++ll)
    {
      l = m - ll;
      if (l == 0)
        break;
      test = cabsm(s[l - 1]) + cabsm(s[l + 1 - 1]);
      ztest = test + cabsm(e[l - 1]);
      if (ztest == test)
      {
        e[l - 1] = S(0);
        break;
      }
    }
    if (l == m - 1)
    {
      kase = 4;
    }
    else
    {
      lp1 = l + 1;
      mp1 = m + 1;
      for (lls = lp1; lls <= mp1; ++lls)
      {
        ls = m - lls + lp1;
        if (ls == l)
          break;
        test = R(0);
        if (ls != m)
          test = test + cabsm(e[ls - 1]);
        if (ls != l + 1)
          test = test + cabsm(e[ls - 1 - 1]);
        ztest = test + cabsm(s[ls - 1]);
        if (ztest == test)
        {
          s[ls - 1] = S(0);
          break;
        }
      }
      if (ls == l)
      {
        kase = 3;
      }
      else if (ls == m)
      {
        kase = 1;
      }
      else
      {
        kase = 2;
        l = ls;
      }
    }
    l = l + 1;

    switch (kase)
    {
      case 1:
      {
        mm1 = m - 1;
        f = e[m - 1 - 1].real();
        e[m - 1 - 1] = S(0);
        for (kk = l; kk <= mm1; ++kk)
        {
          k = mm1 - kk + l;
          t1 = s[k - 1].real();
          blas_rotg(t1, f, cs, sn);
          s[k - 1] = S(t1, R(0));
          if (k != l)
          {
            f = -sn * e[k - 1 - 1].real();
            e[k - 1 - 1] = cs * e[k - 1 - 1];
          }
          if (wantv)
            blas_csrot(p, ADDR(v, ldv, 1, k), one, ADDR(v, ldv, 1, m), one, cs, sn);
        }
        break;
      }
      case 2:
      {
        f = e[l - 1 - 1].real();
        e[l - 1 - 1] = S(0);
        for (k = l; k <= m; ++k)
        {
          t1 = s[k - 1].real();
          blas_rotg(t1, f, cs, sn);
          s[k - 1] = S(t1, R(0));
          f = -sn * e[k - 1].real();
          e[k - 1] = cs * e[k - 1];
          if (wantu)
            blas_csrot(n, ADDR(u, ldu, 1, k), one, ADDR(u, ldu, 1, l - 1), one, cs, sn);
        }
        break;
      }
      case 3:
      {
        {
          R a1 = cabsm(s[m - 1]), a2 = cabsm(s[m - 1 - 1]), a3 = cabsm(e[m - 1 - 1]), a4 = cabsm(s[l - 1]),
            a5 = cabsm(e[l - 1]);
          scale = a1;
          if (a2 > scale)
            scale = a2;
          if (a3 > scale)
            scale = a3;
          if (a4 > scale)
            scale = a4;
          if (a5 > scale)
            scale = a5;
        }
        sm = s[m - 1].real() / scale;
        smm1 = s[m - 1 - 1].real() / scale;
        emm1 = e[m - 1 - 1].real() / scale;
        sl = s[l - 1].real() / scale;
        el = e[l - 1].real() / scale;
        b = ((smm1 + sm) * (smm1 - sm) + emm1 * emm1) / R(2);
        c = (sm * emm1) * (sm * emm1);
        shift = R(0);
        if (b != R(0) || c != R(0))
        {
          shift = fsqrt(b * b + c);
          if (b < R(0))
            shift = -shift;
          shift = c / (b + shift);
        }
        f = (sl + sm) * (sl - sm) + shift;
        g = sl * el;
        mm1 = m - 1;
        for (k = l; k <= mm1; ++k)
        {
          blas_rotg(f, g, cs, sn);
          if (k != l)
            e[k - 1 - 1] = S(f, R(0));
          f = cs * s[k - 1].real() + sn * e[k - 1].real();
          e[k - 1] = cs * e[k - 1] - sn * s[k - 1];
          g = sn * s[k + 1 - 1].real();
          s[k + 1 - 1] = cs * s[k + 1 - 1];
          if (wantv)
            blas_csrot(p, ADDR(v, ldv, 1, k), one, ADDR(v, ldv, 1, k + 1), one, cs, sn);
          blas_rotg(f, g, cs, sn);
          s[k - 1] = S(f, R(0));
          f = cs * e[k - 1].real() + sn * s[k + 1 - 1].real();
          s[k + 1 - 1] = -sn * e[k - 1] + cs * s[k + 1 - 1];
          g = sn * e[k + 1 - 1].real();
          e[k + 1 - 1] = cs * e[k + 1 - 1];
          if (wantu && k < n)
            blas_csrot(n, ADDR(u, ldu, 1, k), one, ADDR(u, ldu, 1, k + 1), one, cs, sn);
        }
        e[m - 1 - 1] = S(f, R(0));
        iter = iter + 1;
        break;
      }
      case 4:
      {
        if (s[l - 1].real() < R(0))
        {
          s[l - 1] = -s[l - 1];
          if (wantv)
            blas_cscal(p, S(R(-1)), ADDR(v, ldv, 1, l), one);
        }
        while (l != mm)
        {
          if (s[l - 1].real() >= s[l + 1 - 1].real())
            break;
          t = s[l - 1];
          s[l - 1] = s[l + 1 - 1];
          s[l + 1 - 1] = t;
          if (wantv && l < p)
            blas_cswap(p, ADDR(v, ldv, 1, l), one, ADDR(v, ldv, 1, l + 1), one);
          if (wantu && l < n)
            blas_cswap(n, ADDR(u, ldu, 1, l), one, ADDR(u, ldu, 1, l + 1), one);
          l = l + 1;
        }
        iter = 0;
        m = m - 1;
        break;
      }
    }
  }
  return 0;
}

// Convenience aliases matching the netlib symbol names.
inline int
native_ssvdc(float * x, long const * ldx, long const * n, long const * p, float * s, float * e, float * u,
             long const * ldu, float * v, long const * ldv, float * work, long const * job, long * info)
{
  return native_svdc<float>(x, ldx, n, p, s, e, u, ldu, v, ldv, work, job, info);
}
inline int
native_csvdc(std::complex<float> * x, long const * ldx, long const * n, long const * p, std::complex<float> * s,
             std::complex<float> * e, std::complex<float> * u, long const * ldu, std::complex<float> * v,
             long const * ldv, std::complex<float> * work, long const * job, long * info)
{
  return native_csvdc_tmpl<float>(x, ldx, n, p, s, e, u, ldu, v, ldv, work, job, info);
}
inline int
native_zsvdc(std::complex<double> * x, long const * ldx, long const * n, long const * p, std::complex<double> * s,
             std::complex<double> * e, std::complex<double> * u, long const * ldu, std::complex<double> * v,
             long const * ldv, std::complex<double> * work, long const * job, long * info)
{
  return native_csvdc_tmpl<double>(x, ldx, n, p, s, e, u, ldu, v, ldv, work, job, info);
}
inline int
native_dsvdc(double * x, long const * ldx, long const * n, long const * p, double * s, double * e, double * u,
             long const * ldu, double * v, long const * ldv, double * work, long const * job, long * info)
{
  return native_svdc<double>(x, ldx, n, p, s, e, u, ldu, v, ldv, work, job, info);
}


// Overloaded entry point so the vnl_svd*.hxx macros dispatch by scalar type.
inline int
vnl_native_svdc(float * x, long const * ldx, long const * n, long const * p, float * s, float * e, float * u,
                long const * ldu, float * v, long const * ldv, float * work, long const * job, long * info)
{
  return native_svdc<float>(x, ldx, n, p, s, e, u, ldu, v, ldv, work, job, info);
}
inline int
vnl_native_svdc(double * x, long const * ldx, long const * n, long const * p, double * s, double * e, double * u,
                long const * ldu, double * v, long const * ldv, double * work, long const * job, long * info)
{
  return native_svdc<double>(x, ldx, n, p, s, e, u, ldu, v, ldv, work, job, info);
}
inline int
vnl_native_svdc(std::complex<float> * x, long const * ldx, long const * n, long const * p, std::complex<float> * s,
                std::complex<float> * e, std::complex<float> * u, long const * ldu, std::complex<float> * v,
                long const * ldv, std::complex<float> * work, long const * job, long * info)
{
  return native_csvdc_tmpl<float>(x, ldx, n, p, s, e, u, ldu, v, ldv, work, job, info);
}
inline int
vnl_native_svdc(std::complex<double> * x, long const * ldx, long const * n, long const * p, std::complex<double> * s,
                std::complex<double> * e, std::complex<double> * u, long const * ldu, std::complex<double> * v,
                long const * ldv, std::complex<double> * work, long const * job, long * info)
{
  return native_csvdc_tmpl<double>(x, ldx, n, p, s, e, u, ldu, v, ldv, work, job, info);
}

#endif // vnl_svd_native_h_
