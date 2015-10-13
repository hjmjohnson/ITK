set(DOCUMENTATION "This module contains the base classes needed to implement
finite differences image filters. They include both sparse and dense finite
differences. Most of the classes in this module are abstract and therefore are
not intended to be instantiated by themselves.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKFiniteDifference_Shared "ENABLE_SHARED")
endif()

itk_module(ITKFiniteDifference
  ${ITKFiniteDifference_Shared}
  COMPILE_DEPENDS
    ITKCommon
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
