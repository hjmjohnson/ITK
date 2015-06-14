file(GLOB ITK_IOSPATIALOBJECTS_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKIOSpatialObjects_SRCS
  itkPolygonGroupSpatialObjectXMLFile.cxx
  ${ITK_IOSPATIALOBJECTS_EXPLICIT_SOURCES}
  )

itk_module_add_library(ITKIOSpatialObjects ${ITKIOSpatialObjects_SRCS})
