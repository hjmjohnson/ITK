if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_TRANSFORM_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_TRANSFORM_EXPLICIT_SOURCES "")
endif()

set(ITKTransform_SRCS
${ITK_TRANSFORM_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKTransform_SRCS)
  add_library(ITKTransform ${ITK_LIBRARY_BUILD_TYPE} ${ITKTransform_SRCS})
  itk_module_link_dependencies()
  itk_module_target(ITKTransform)
endif()
