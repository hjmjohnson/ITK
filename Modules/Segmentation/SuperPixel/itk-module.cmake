set(DOCUMENTATTION "This modules contains classes related to
superpixel segmentation and clustering algorithms.")


# define the dependencies of the include module and the tests
itk_module(ITKSuperPixel
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKCommon
    ITKStatistics
    ITKImageGrid
  DEPENDS ## COMPILE_DEPENDS
    ITKImageSources
  TEST_DEPENDS
    ITKTestKernel
    ITKGoogleTest
    ITKMetaIO
  DESCRIPTION
    "${DOCUMENTATION}"
)
