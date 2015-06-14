file(GLOB ITK_WATERSHEDS_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKWatersheds_SRCS
  itkWatershedMiniPipelineProgressCommand.cxx
  itkOneWayEquivalencyTable.cxx
  ${ITK_WATERSHEDS_EXPLICIT_SOURCES}
  )

itk_module_add_library(ITKWatersheds ${ITKWatersheds_SRCS})
