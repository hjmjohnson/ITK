itk_module_test()

set(
  BoneEnhancementUnitTests
  itkDescoteauxEigenToMeasureParameterEstimationFilterUnitTest.cxx
  itkDescoteauxEigenToMeasureImageFilterUnitTest.cxx
  itkHessianGaussianImageFilterGTest.cxx
  itkKrcahEigenToMeasureParameterEstimationFilterUnitTest.cxx
  itkMaximumAbsoluteValueImageFilterGTest.cxx
  itkMultiScaleHessianEnhancementImageFilterStaticMethodsGTest.cxx
)

creategoogletestdriver(BoneEnhancementUnitTests "${BoneEnhancement-Test_LIBRARIES}" "${BoneEnhancementUnitTests}")
