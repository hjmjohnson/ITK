if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_FINITEDIFFERENCE_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_FINITEDIFFERENCE_EXPLICIT_SOURCES "")
endif()

set(ITKFiniteDifference_SRC
${ITK_FINITEDIFFERENCE_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKFiniteDifference_SRC)
  add_library(ITKFiniteDifference ${ITKFiniteDifference_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKFiniteDifference)
endif()
