set(DOCUMENTATION "SpatialObjects are intended to represent regions in space.
The basic functionality of a SpatialObject is to answer the question of
whether a physical point is inside or outside of the SpatialObject. They are
commonly used for representing masks in an analytical form, as well as
approximations of shape by combining them into hierarchical structures similar
to scene graphs.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKSpatialObjects_Shared "ENABLE_SHARED")
else()
  set(ITKSpatialObjects_Shared "")
endif()

itk_module(ITKSpatialObjects
  ${ITKSpatialObjects_Shared}
  PRIVATE_DEPENDS
    ITKMesh
    ITKCommon
  COMPILE_DEPENDS
    ITKImageFunction
    ITKMetaIO
  TEST_DEPENDS
    ITKTestKernel
    ITKMetaIO
    ITKMesh
  DESCRIPTION
    "${DOCUMENTATION}"
)
