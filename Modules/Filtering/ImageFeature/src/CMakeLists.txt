if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IMAGFEATURE_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IMAGFEATURE_EXPLICIT_SOURCES "")
endif()

set(ITKImageFeature_SRC
${ITK_IMAGFEATURE_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKImageFeature_SRC)
  add_library(ITKImageFeature ${ITKImageFeature_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKImageFeature)
endif()
