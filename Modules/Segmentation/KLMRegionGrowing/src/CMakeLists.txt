if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_KLMREGIONGROWING_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_KLMREGIONGROWING_EXPLICIT_SOURCES "")
endif()

set(ITKKLMRegionGrowing_SRC
itkSegmentationRegion.cxx
itkKLMSegmentationRegion.cxx
itkSegmentationBorder.cxx
itkKLMSegmentationBorder.cxx

${ITK_KLMREGIONGROWING_EXPLICIT_SOURCES}
)

add_library(ITKKLMRegionGrowing ${ITKKLMRegionGrowing_SRC})
itk_module_link_dependencies()
itk_module_target(ITKKLMRegionGrowing)
