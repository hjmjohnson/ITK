set(DOCUMENTATION "This module contains implementations of generalized versions
of the Fast Marching filter. These implementations cover the use of Fast
Marching in both itk::Images and itk::QuadEdgeMeshes.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKFastMarching_Shared "ENABLE_SHARED")
endif()

itk_module(ITKFastMarching
  ${ITKFastMarching_Shared}
  COMPILE_DEPENDS
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
