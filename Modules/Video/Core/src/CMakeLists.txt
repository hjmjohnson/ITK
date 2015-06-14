file(GLOB ITK_VIDEOCORE_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKVideoCore_SRCS
  itkTemporalRegion.cxx
  itkTemporalDataObject.cxx
  itkTemporalProcessObject.cxx
  ${ITK_VIDEOCORE_EXPLICIT_SOURCES}
  )

itk_module_add_library(ITKVideoCore ${ITKVideoCore_SRCS})
