if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_VIDEOCORE_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_VIDEOCORE_EXPLICIT_SOURCES "")
endif()

set(ITKVideoCore_SRC
itkTemporalRegion.cxx
itkTemporalDataObject.cxx
itkTemporalProcessObject.cxx

${ITK_VIDEOCORE_EXPLICIT_SOURCES}
)

add_library(ITKVideoCore ${ITKVideoCore_SRC})
itk_module_link_dependencies()
itk_module_target(ITKVideoCore)
