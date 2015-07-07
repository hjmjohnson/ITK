if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IMAGEFUNCTION_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IMAGEFUNCTION_EXPLICIT_SOURCES "")
endif()

set(ITKImageFunction_SRC
${ITK_IMAGEFUNCTION_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKImageFunction_SRC)
  add_library(ITKImageFunction ${ITKImageFunction_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKImageFunction)
endif()
