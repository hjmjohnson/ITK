itk_module_test()

set(
  BoneEnhancementTests
  itkMaximumAbsoluteValueImageFilterTest.cxx
  itkMultiScaleHessianEnhancementImageFilterStaticMethodsTest.cxx
)

createtestdriver(BoneEnhancement "${BoneEnhancement-Test_LIBRARIES}" "${BoneEnhancementTests}")

itk_add_test(
  NAME itkMaximumAbsoluteValueImageFilterTest
  COMMAND
    BoneEnhancementTestDriver
    itkMaximumAbsoluteValueImageFilterTest
)

itk_add_test(
  NAME itkMultiScaleHessianEnhancementImageFilterStaticMethodsTest
  COMMAND
    BoneEnhancementTestDriver
    itkMultiScaleHessianEnhancementImageFilterStaticMethodsTest
)

set(
  BoneEnhancementUnitTests
  itkDescoteauxEigenToMeasureParameterEstimationFilterUnitTest.cxx
  itkDescoteauxEigenToMeasureImageFilterUnitTest.cxx
  itkHessianGaussianImageFilterGTest.cxx
  itkKrcahEigenToMeasureParameterEstimationFilterUnitTest.cxx
)

creategoogletestdriver(BoneEnhancementUnitTests "${BoneEnhancement-Test_LIBRARIES}" "${BoneEnhancementUnitTests}")
