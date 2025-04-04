// This is core/vnl/vnl_complexify.h
#ifndef vnl_complexify_h_
#define vnl_complexify_h_
//:
//  \file
//  \brief Functions to create complex vectors and matrices from real ones
//  \author fsm
//
// \verbatim
// Modifications
// Peter Vanroose - 2 July 2002 - part of vnl_complex_ops.h moved here
// \endverbatim

#include <complex>
#ifdef _MSC_VER
#  include <vcl_msvc_warnings.h>
#endif
#include "vnl_vector.h"
#include "vnl_vector_fixed.h"
#include "vnl_matrix.h"
#include "vnl_matrix_fixed.h"
#include "vnl_diag_matrix.h"
#include "vnl_diag_matrix_fixed.h"
#include "vnl_sym_matrix.h"
#include "vnl/vnl_export.h"

//: Overwrite complex array C (of length n) with pairs from real arrays R and I.
template <class T>
VNL_EXPORT void
vnl_complexify(const T * R, const T * I, std::complex<T> * C, unsigned n);
//: Overwrite complex array C (sz n) with complexified version of real array R.
template <class T>
VNL_EXPORT void
vnl_complexify(const T * R, std::complex<T> * C, unsigned n);

// Real Alone:
// - vnl_vector
// - vnl_vector_fixed
// - vnl_matrix
// - vnl_matrix_fixed
// - vnl_diag_matrix
// - vnl_diag_matrix_fixed
// - vnl_sym_matrix

//: Return complexified version of real vector R.
// \relatesalso vnl_vector
template <class T>
VNL_EXPORT vnl_vector<std::complex<T>>
vnl_complexify(const vnl_vector<T> & R);


template <class T, unsigned int n>
VNL_EXPORT vnl_vector_fixed<std::complex<T>, n>
vnl_complexify(const vnl_vector_fixed<T, n> & R);

//: Return complexified version of real fixed vector R.
// \relatesalso vnl_vector_fixed
template <class T, unsigned int n>
vnl_vector_fixed<std::complex<T>, n>
vnl_complexify(const vnl_vector_fixed<T, n> & R)
{
  vnl_vector_fixed<std::complex<T>, n> C;
  vnl_complexify(R.begin(), C.begin(), R.size());
  return C;
}

//: Return complexified version of real matrix R.
// \relatesalso vnl_matrix
template <class T>
VNL_EXPORT vnl_matrix<std::complex<T>>
vnl_complexify(const vnl_matrix<T> & R);

//: Return complexified version of real fixed matrix R.
// \relatesalso vnl_matrix_fixed
template <class T, unsigned int r, unsigned int c>
VNL_EXPORT vnl_matrix_fixed<std::complex<T>, r, c>
vnl_complexify(const vnl_matrix_fixed<T, r, c> & R);

template <class T, unsigned int r, unsigned int c>
vnl_matrix_fixed<std::complex<T>, r, c>
vnl_complexify(const vnl_matrix_fixed<T, r, c> & R)
{
  vnl_matrix_fixed<std::complex<T>, r, c> C;
  vnl_complexify(R.begin(), C.begin(), R.size());
  return C;
}

//: Return complexified version of real diagonal matrix R.
// \relatesalso vnl_diag_matrix
template <class T>
VNL_EXPORT vnl_diag_matrix<std::complex<T>>
vnl_complexify(const vnl_diag_matrix<T> & R);

//: Return complexified version of real fixed diagonal matrix R.
// \relatesalso vnl_diag_matrix_fixed
template <class T, unsigned int n>
vnl_diag_matrix_fixed<std::complex<T>, n>
vnl_complexify(const vnl_diag_matrix_fixed<T, n> & R)
{
  vnl_diag_matrix_fixed<std::complex<T>, n> C;
  vnl_complexify(R.begin(), C.begin(), R.size());
  return C;
}

//: Return complexified version of real symmetric matrix R.
// \relatesalso vnl_sym_matrix
template <class T>
VNL_EXPORT vnl_sym_matrix<std::complex<T>>
vnl_complexify(const vnl_sym_matrix<T> & R);

//----------------------------------------------------------------------

// Real + Imaginary:
// - vnl_vector
// - vnl_vector_fixed
// - vnl_matrix
// - vnl_matrix_fixed
// - vnl_diag_matrix
// - vnl_diag_matrix_fixed
// - vnl_sym_matrix

//: Return complex vector R+j*I from two real vectors R and I.
// \relatesalso vnl_vector
template <class T>
VNL_EXPORT vnl_vector<std::complex<T>>
vnl_complexify(const vnl_vector<T> & R, const vnl_vector<T> & I);

//: Return complex fixed vector R+j*I from two real fixed vectors R and I.
// \relatesalso vnl_vector_fixed
template <class T, unsigned int n>
vnl_vector_fixed<std::complex<T>, n>
vnl_complexify(const vnl_vector_fixed<T, n> & R, const vnl_vector_fixed<T, n> & I)
{
  vnl_vector_fixed<std::complex<T>, n> C;
  vnl_complexify(R.begin(), I.begin(), C.begin(), R.size());
  return C;
}

//: Return complex matrix R+j*I from two real matrices R and I.
// \relatesalso vnl_matrix
template <class T>
VNL_EXPORT vnl_matrix<std::complex<T>>
vnl_complexify(const vnl_matrix<T> & R, const vnl_matrix<T> & I);

//: Return complex fixed matrix R+j*I from two real fixed matrices R and I.
// \relatesalso vnl_matrix_fixed
template <class T, unsigned int r, unsigned int c>
vnl_matrix_fixed<std::complex<T>, r, c>
vnl_complexify(const vnl_matrix_fixed<T, r, c> & R, const vnl_matrix_fixed<T, r, c> & I)
{
  vnl_matrix_fixed<std::complex<T>, r, c> C;
  vnl_complexify(R.begin(), I.begin(), C.begin(), R.size());
  return C;
}

//: Return complex diagonal matrix R+j*I from two real diagonal matrices R and I.
// \relatesalso vnl_diag_matrix
template <class T>
VNL_EXPORT vnl_diag_matrix<std::complex<T>>
vnl_complexify(const vnl_diag_matrix<T> & R, const vnl_diag_matrix<T> & I);

//: Return complex fixed diagonal matrix R+j*I from two real fixed diagonal matrices R and I.
// \relatesalso vnl_matrix_fixed
template <class T, unsigned int n>
vnl_diag_matrix_fixed<std::complex<T>, n>
vnl_complexify(const vnl_diag_matrix_fixed<T, n> & R, const vnl_diag_matrix_fixed<T, n> & I)
{
  vnl_diag_matrix_fixed<std::complex<T>, n> C;
  vnl_complexify(R.begin(), I.begin(), C.begin(), R.size());
  return C;
}

//: Return complex diagonal matrix R+j*I from two real diagonal matrices R and I.
// \relatesalso vnl_diag_matrix
template <class T>
VNL_EXPORT vnl_sym_matrix<std::complex<T>>
vnl_complexify(const vnl_sym_matrix<T> & R, const vnl_sym_matrix<T> & I);

#endif // vnl_complexify_h_
