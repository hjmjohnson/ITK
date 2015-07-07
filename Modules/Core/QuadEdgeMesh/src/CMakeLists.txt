if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_COMMON_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_COMMON_EXPLICIT_SOURCES "")
endif()

set(ITKQuadEdgeMesh_SRC
itkQuadEdge.cxx

${ITK_COMMON_EXPLICIT_SOURCES}
)

add_library(ITKQuadEdgeMesh ${ITKQuadEdgeMesh_SRC})
itk_module_link_dependencies()
itk_module_target(ITKQuadEdgeMesh)
