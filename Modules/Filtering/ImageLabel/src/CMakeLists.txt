if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IMAGELABEL_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IMAGELABEL_EXPLICIT_SOURCES "")
endif()

set(ITKImageLabel_SRC
${ITK_IMAGELABEL_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKImageLabel_SRC)
  add_library(ITKImageLabel ${ITKImageLabel_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKImageLabel)
endif()
