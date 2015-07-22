if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_WATERSHEDS_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_VORONOI_WATERSHEDS_SOURCES "")
endif()

set(ITKWatersheds_SRC
itkWatershedMiniPipelineProgressCommand.cxx
itkOneWayEquivalencyTable.cxx

${ITK_WATERSHEDS_EXPLICIT_SOURCES}
)

add_library(ITKWatersheds ${ITKWatersheds_SRC})
itk_module_link_dependencies()
itk_module_target(ITKWatersheds)
