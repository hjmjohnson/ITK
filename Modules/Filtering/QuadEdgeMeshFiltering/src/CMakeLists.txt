if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_QUADEDGEMESHFILTERING_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_QUADEDGEMESHFILTERING_EXPLICIT_SOURCES "")
endif()

set(ITKQuadEdgeMeshFiltering_SRC
${ITK_QUADEDGEMESHFILTERING_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKQuadEdgeMeshFiltering_SRC)
  add_library(ITKQuadEdgeMeshFiltering ${ITKQuadEdgeMeshFiltering_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKQuadEdgeMeshFiltering)
endif()
