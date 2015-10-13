set(DOCUMENTATION "This module contains typical examples of regitration methods based upon the high dimensional metrics and high dimensional optimizers.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKRegistrationMethodsv4_Shared "ENABLE_SHARED")
endif()

itk_module(ITKRegistrationMethodsv4
  ${ITKRegistrationMethodsv4_Shared}
  DEPENDS
    ITKOptimizersv4
    ITKMetricsv4
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
