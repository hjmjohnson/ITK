file(GLOB ITK_COMMON_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKQuadEdgeMesh_SRCS
  itkQuadEdge.cxx
  ${ITK_COMMON_EXPLICIT_SOURCES}
  )

itk_module_add_library(ITKQuadEdgeMesh ${ITKQuadEdgeMesh_SRCS})
