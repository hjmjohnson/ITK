set(
  DOCUMENTATION
  "This module contains classes for reading and writing
Meshes in the Gifti file format."
)
itk_module(
  ITKIOMeshGifti
  ENABLE_SHARED
  DEPENDS
    ITKCommon
    ITKIOMeshBase
  PRIVATE_DEPENDS
    ITKGIFTI
    ITKMesh
  TEST_DEPENDS
    ITKTestKernel
    ITKQuadEdgeMesh
  FACTORY_NAMES
    MeshIO::Gifti
  DESCRIPTION "${DOCUMENTATION}"
)
