if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_THRESHOLDING_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_THRESHOLDING_EXPLICIT_SOURCES "")
endif()

set(ITKThresholding_SRC
${ITK_THRESHOLDING_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKThresholding_SRC)
  add_library(ITKThresholding ${ITKThresholding_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKThresholding)
endif()
