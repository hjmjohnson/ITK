if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IMAGEFUSION_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IMAGEFUSION_EXPLICIT_SOURCES "")
endif()

set(ITKImageFusion_SRC
${ITK_IMAGEFUSION_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKImageFusion_SRC)
  add_library(ITKImageFusion ${ITKImageFusion_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKImageFusion)
endif()
