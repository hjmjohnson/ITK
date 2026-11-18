set(
  DOCUMENTATION
  "This module contains the base classes for the input and output
of itkTransform objects."
)

itk_module(
  ITKIOTransformBase
  ENABLE_SHARED
  DEPENDS
    ITKCommon
    ITKTransform
    ITKTransformFactory
  PRIVATE_DEPENDS
    ITKDisplacementField
  TEST_DEPENDS
    ITKGoogleTest
    ITKTestKernel
  DESCRIPTION "${DOCUMENTATION}"
)
