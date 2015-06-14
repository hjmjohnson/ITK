file(GLOB ITK_MESH_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKMesh_SRCS
  itkMeshRegion.cxx
  itkSimplexMeshGeometry.cxx
  ${ITK_MESH_EXPLICIT_SOURCES}
  )

itk_module_add_library(ITKMesh ${ITKMesh_SRCS})
