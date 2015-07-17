if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_OPTIMIZERSV4_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_OPTIMIZERSV4_EXPLICIT_SOURCES "")
endif()

set(ITKOptimizersv4_SRC
  itkSingleValuedNonLinearVnlOptimizerv4.cxx
  itkSingleValuedVnlCostFunctionAdaptorv4.cxx
  itkLBFGSOptimizerv4.cxx
  itkLBFGSBOptimizerv4.cxx
  itkAmoebaOptimizerv4.cxx

  ${ITK_OPTIMIZERSV4_EXPLICIT_SOURCES}
)

add_library(ITKOptimizersv4 ${ITKOptimizersv4_SRC})
itk_module_link_dependencies()
target_link_libraries(ITKOptimizersv4 LINK_PUBLIC ${ITKMetricsv4_LIBRARIES})
itk_module_target(ITKOptimizersv4)
