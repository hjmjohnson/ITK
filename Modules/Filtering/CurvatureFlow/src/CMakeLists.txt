if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_CURVATUREFLOW_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_CURVATUREFLOW_EXPLICIT_SOURCES "")
endif()

set(ITKCurvatureFlow_SRC
${ITK_CURVATUREFLOW_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKCurvatureFlow_SRC)
  add_library(ITKCurvatureFlow ${ITKCurvatureFlow_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKCurvatureFlow)
endif()
