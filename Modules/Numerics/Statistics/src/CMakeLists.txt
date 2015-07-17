if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_STATISTICS_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_STATISTICS_EXPLICIT_SOURCES "")
endif()

set(ITKStatistics_SRC
itkProbabilityDistribution.cxx
itkDenseFrequencyContainer2.cxx
itkSparseFrequencyContainer2.cxx
itkChiSquareDistribution.cxx
itkGaussianDistribution.cxx
itkTDistribution.cxx
itkNormalVariateGenerator.cxx
itkDecisionRule.cxx
itkMaximumDecisionRule.cxx
itkMaximumRatioDecisionRule.cxx
itkMinimumDecisionRule.cxx

${ITK_STATISTICS_EXPLICIT_SOURCES}
)

add_library(ITKStatistics ${ITKStatistics_SRC})
itk_module_link_dependencies()
itk_module_target(ITKStatistics)
