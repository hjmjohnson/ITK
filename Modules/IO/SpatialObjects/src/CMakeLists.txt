if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IOSPATIALOBJECTS_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IOSPATIALOBJECTS_EXPLICIT_SOURCES "")
endif()

set(ITKIOSpatialObjects_SRC
itkPolygonGroupSpatialObjectXMLFile.cxx
${ITK_IOSPATIALOBJECTS_EXPLICIT_SOURCES}
)

add_library(ITKIOSpatialObjects ${ITKIOSpatialObjects_SRC})
itk_module_link_dependencies()
itk_module_target(ITKIOSpatialObjects)
