file(GLOB ITK_KLMREGIONGROWING_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKKLMRegionGrowing_SRCS
  itkSegmentationRegion.cxx
  itkKLMSegmentationRegion.cxx
  itkSegmentationBorder.cxx
  itkKLMSegmentationBorder.cxx
  ${ITK_KLMREGIONGROWING_EXPLICIT_SOURCES}
  )

itk_module_add_library(ITKKLMRegionGrowing ${ITKKLMRegionGrowing_SRCS})
