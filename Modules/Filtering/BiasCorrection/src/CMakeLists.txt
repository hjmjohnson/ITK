if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_BIASCORRECTION_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_BIASCORRECTION_EXPLICIT_SOURCES "")
endif()

set(ITKBiasCorrection_SRC
itkCompositeValleyFunction.cxx
itkCacheableScalarFunction.cxx

${ITK_BIASCORRECTION_EXPLICIT_SOURCES}
)

add_library(ITKBiasCorrection ${ITKBiasCorrection_SRC})
itk_module_link_dependencies()
itk_module_target(ITKBiasCorrection)
