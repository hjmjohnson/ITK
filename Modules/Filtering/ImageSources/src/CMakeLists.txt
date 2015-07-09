if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IMAGESOURCES_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IMAGESOURCES_EXPLICIT_SOURCES "")
endif()

set(ITKImageSources_SRC
${ITK_IMAGESOURCES_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKImageSources_SRC)
  add_library(ITKImageSources ${ITKImageSources_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKImageSources)
endif()
