itk_module_test()
set(
  ITKDiffusionTensorImageTests
  itkDiffusionTensor3DReconstructionImageFilterTest.cxx
  itkTensorFractionalAnisotropyImageFilterTest.cxx
)

createtestdriver(ITKDiffusionTensorImage "${ITKDiffusionTensorImage-Test_LIBRARIES}" "${ITKDiffusionTensorImageTests}")

itk_add_test(
  NAME itkDiffusionTensor3DReconstructionImageFilterTest
  COMMAND
    ITKDiffusionTensorImageTestDriver
    itkDiffusionTensor3DReconstructionImageFilterTest
    1.0
)
itk_add_test(
  NAME itkTensorFractionalAnisotropyImageFilterTest
  COMMAND
    ITKDiffusionTensorImageTestDriver
    itkTensorFractionalAnisotropyImageFilterTest
)

set(
  ITKDiffusionTensorImageGTests
  itkDiffusionTensor3DGTest.cxx
  itkDiffusionTensor3DReconstructionSingleImageGTest.cxx
  itkTensorRelativeAnisotropyImageFilterGTest.cxx
)
creategoogletestdriver(ITKDiffusionTensorImage "${ITKDiffusionTensorImage-Test_LIBRARIES}" "${ITKDiffusionTensorImageGTests}")
