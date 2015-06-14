if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IMAGECOMPOSE_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IMAGECOMPOSE_EXPLICIT_SOURCES "")
endif()

set(ITKImageCompose_SRC
${ITK_IMAGECOMPOSE_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKImageCompose_SRC)
  add_library(ITKImageCompose ${ITKImageCompose_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKImageCompose)
endif()
