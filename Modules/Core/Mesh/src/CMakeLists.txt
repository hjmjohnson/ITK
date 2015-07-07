if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_MESH_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_MESH_EXPLICIT_SOURCES "")
endif()

set(ITKMesh_SRC
itkMeshRegion.cxx
itkSimplexMeshGeometry.cxx

${ITK_MESH_EXPLICIT_SOURCES}
)

add_library(ITKMesh ${ITKMesh_SRC})
itk_module_link_dependencies()
itk_module_target(ITKMesh)
