set(DOCUMENTATION "This module contains implementations of generalized versions
of the Fast Marching filter. These implementations cover the use of Fast
Marching in both itk::Images and itk::QuadEdgeMeshes.")

itk_module(ITKFastMarching
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS ## COMPILE_DEPENDS
    ITKMesh
    ITKQuadEdgeMesh
    ITKConnectedComponents
  TEST_DEPENDS
    ITKTestKernel
    ITKImageLabel
    ITKIOMesh
  DESCRIPTION
    "${DOCUMENTATION}"
)
