if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IMAGEGRADIENT_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IMAGEGRADIENT_EXPLICIT_SOURCES "")
endif()

set(ITKImageGradient_SRC
${ITK_IMAGEGRADIENT_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKImageGradient_SRC)
  add_library(ITKImageGradient ${ITKImageGradient_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKImageGradient)
endif()
