itk_module_test()
set(
  ITKDiffusionTensorImageTests
  itkDiffusionTensor3DReconstructionImageFilterTest.cxx
)

createtestdriver(ITKDiffusionTensorImage "${ITKDiffusionTensorImage-Test_LIBRARIES}" "${ITKDiffusionTensorImageTests}")

itk_add_test(
  NAME itkDiffusionTensor3DReconstructionImageFilterTest
  COMMAND
    ITKDiffusionTensorImageTestDriver
    itkDiffusionTensor3DReconstructionImageFilterTest
    1.0
)

set(
  ITKDiffusionTensorImageGTests
  itkDiffusionTensor3DGTest.cxx
  itkDiffusionTensor3DReconstructionSingleImageGTest.cxx
  itkTensorFractionalAnisotropyImageFilterGTest.cxx
  itkTensorRelativeAnisotropyImageFilterGTest.cxx
)
creategoogletestdriver(ITKDiffusionTensorImage "${ITKDiffusionTensorImage-Test_LIBRARIES}" "${ITKDiffusionTensorImageGTests}")
