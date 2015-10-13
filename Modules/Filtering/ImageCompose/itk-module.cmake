set(DOCUMENTATION "This module contains filters that combine several images
into a single output image. For example, take several input scalar images and
package them into an output image of multiple components.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKImageCompose_Shared "ENABLE_SHARED")
endif()

itk_module(ITKImageCompose
  ${ITKImageCompose_Shared}
  COMPILE_DEPENDS
    ITKImageFilterBase
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
