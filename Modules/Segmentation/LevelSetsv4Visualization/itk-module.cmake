set(DOCUMENTATION "This module constains classes related to the
visualization of the level-sets.")

itk_module( ITKLevelSetsv4Visualization
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKLevelSetsv4
    ITKVtkGlue
  TEST_DEPENDS
    ITKTestKernel
    EXCLUDE_FROM_DEFAULT
  DESCRIPTION
   "${DOCUMENTATION}"
  )
