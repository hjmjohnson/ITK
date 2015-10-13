set(DOCUMENTATION "This module contains filters intended to operate on images
of labels. Such images are typically the output of segmentation and
classification filters, such as watersheds or statistical classifiers. The
filters in this module compute label statistics and perform operations between
labels.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKImageLabel_Shared "ENABLE_SHARED")
endif()

itk_module(ITKImageLabel
  ${ITKImageLabel_Shared}
  COMPILE_DEPENDS
    ITKImageFilterBase
    ITKImageIntensity
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
