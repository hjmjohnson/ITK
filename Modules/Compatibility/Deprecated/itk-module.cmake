set(DOCUMENTATION "This is a collection of classes that are intended to be
removed from the toolkit.")

set(ITKDeprecatedOnByDefault EXCLUDE_FROM_DEFAULT)
if (ITKV4_COMPATIBILITY)
  set(ITKDeprecatedOnByDefault "")
endif()

itk_module(ITKDeprecated
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKCommon
  TEST_DEPENDS
    ITKTestKernel
  ${ITKDeprecatedOnByDefault}
  ENABLE_SHARED
  DESCRIPTION
    "${DOCUMENTATION}"
)
