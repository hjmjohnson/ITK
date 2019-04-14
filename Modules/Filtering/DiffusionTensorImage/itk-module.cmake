set(DOCUMENTATION "This module contains classes intended to generate or procees
diffusion tensor images. In particular you will find here the filter that
computes a tensor image from a set of gradient images.")

itk_module(ITKDiffusionTensorImage
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS ## COMPILE_DEPENDS
    ITKSpatialObjects
  TEST_DEPENDS
    ITKTestKernel
    ITKImageFeature
  DESCRIPTION
    "${DOCUMENTATION}"
)
