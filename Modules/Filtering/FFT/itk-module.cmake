set(DOCUMENTATION "This module provides interfaces to FFT
implementations. In particular it provides the direct and inverse
computations of Fast Fourier Transforms based on
<a href=\"http://vxl.sourceforge.net/\">VXL</a> and
<a href=\"http://www.fftw.org\">FFTW</a>. Note that when using the FFTW
implementation you must comply with the GPL license.")

if( ITK_USE_FFTWF OR ITK_USE_FFTWD )
  set(FFT_ENABLE_SHARED "ENABLE_SHARED")
endif()

itk_module(ITKFFT
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  ${FFT_ENABLE_SHARED}
  PRIVATE_DEPENDS
    ITKCommon
  DEPENDS ## COMPILE_DEPENDS
    ITKImageGrid
  TEST_DEPENDS
    ITKTestKernel
    ITKImageCompare
  DESCRIPTION
    "${DOCUMENTATION}"
)
