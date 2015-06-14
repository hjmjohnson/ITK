file(GLOB ITK_SPATIAL_OBJECTS_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKSpatialObjects_SRCS
  itkMetaEvent.cxx
  itkSpatialObjectFactoryBase.cxx
  itkSpatialObjectProperty.cxx
  ${ITK_SPATIAL_OBJECTS_EXPLICIT_SOURCES}
 )

itk_module_add_library(ITKSpatialObjects ${ITKSpatialObjects_SRCS})
