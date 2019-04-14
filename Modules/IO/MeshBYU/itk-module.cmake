set(DOCUMENTATION "This module contains classes for reading and writing
Meshes in the BYU file format.")
itk_module(ITKIOMeshBYU
  ENABLE_SHARED
  DEPENDS
    ITKCommon
    ITKIOMeshBase
  DEPENDS ## COMPILE_DEPENDS
    ITKMesh
  TEST_DEPENDS
    ITKTestKernel
    ITKQuadEdgeMesh
  FACTORY_NAMES
    MeshIO::BYU
  DESCRIPTION
    "${DOCUMENTATION}"
)
