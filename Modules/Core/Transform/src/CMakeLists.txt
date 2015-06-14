file(GLOB ITK_TRANSFORM_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKTransform_SRCS
  itkTransformBase.cxx
  ${ITK_TRANSFORM_EXPLICIT_SOURCES}
  )

itk_module_add_library(ITKTransform ${ITKTransform_SRCS})
