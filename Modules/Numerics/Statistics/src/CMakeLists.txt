file(GLOB ITK_STATISTICS_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKStatistics_SRCS
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

itk_module_add_library(ITKStatistics ${ITKStatistics_SRCS})
