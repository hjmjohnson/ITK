if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IMAGEADAPTORS_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IMAGEADAPTORS_EXPLICIT_SOURCES "")
endif()

set(ITKImageAdaptors_SRC
${ITK_IMAGEADAPTORS_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKImageAdaptors_SRC)
  add_library(ITKImageAdaptors ${ITKImageAdaptors_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKImageAdaptors)
endif()
