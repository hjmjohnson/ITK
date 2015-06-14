file(GLOB ITK_BIASCORRECTION_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKBiasCorrection_SRCS
  itkCompositeValleyFunction.cxx
  itkCacheableScalarFunction.cxx

  ${ITK_BIASCORRECTION_EXPLICIT_SOURCES}
  )

itk_module_add_library(ITKBiasCorrection ${ITKBiasCorrection_SRCS})
