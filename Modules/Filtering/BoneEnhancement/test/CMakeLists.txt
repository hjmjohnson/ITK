itk_module_test()

set(
  BoneEnhancementTests
  itkMultiScaleHessianEnhancementImageFilterStaticMethodsTest.cxx
)

createtestdriver(BoneEnhancement "${BoneEnhancement-Test_LIBRARIES}" "${BoneEnhancementTests}")

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
  itkMaximumAbsoluteValueImageFilterGTest.cxx
)

creategoogletestdriver(BoneEnhancementUnitTests "${BoneEnhancement-Test_LIBRARIES}" "${BoneEnhancementUnitTests}")
