if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IMAGEINTENSITY_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IMAGEINTENSITY_EXPLICIT_SOURCES "")
endif()

set(ITKImageIntensity_SRC
${ITK_IMAGEINTENSITY_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKImageIntensity_SRC)
  add_library(ITKImageIntensity ${ITKImageIntensity_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKImageIntensity)
endif()
