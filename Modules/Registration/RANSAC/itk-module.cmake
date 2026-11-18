# the top-level README is used for describing this module, just
# re-used it for documentation here
itk_module(
  RANSAC
  DEPENDS
    ITKCommon
    ITKMesh
    ITKRegistrationCommon
  PRIVATE_DEPENDS
    ITKIOMeshBase
    ITKMetricsv4
    ITKRegistrationMethodsv4
    ITKOptimizersv4
    ITKOptimizers
  ENABLE_SHARED
  TEST_DEPENDS
    ITKTestKernel
    ITKMetaIO
    ITKIOMeshBase
  DESCRIPTION "Module ingested from upstream."
  EXCLUDE_FROM_DEFAULT
)
