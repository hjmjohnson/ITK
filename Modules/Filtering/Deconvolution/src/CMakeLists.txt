if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_DECONVOLUTION_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_DECONVOLUTION_EXPLICIT_SOURCES "")
endif()

set(ITKDeconvolution_SRC
${ITK_DECONVOLUTION_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKDeconvolution_SRC)
  add_library(ITKDeconvolution ${ITKDeconvolution_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKDeconvolution)
endif()
