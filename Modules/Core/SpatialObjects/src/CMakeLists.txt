if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_COMMON_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_COMMON_EXPLICIT_SOURCES "")
endif()

set(ITKSpatialObjects_SRC
itkMetaEvent.cxx
itkCylinderSpatialObject.cxx
itkSpatialObjectFactoryBase.cxx
itkArrowSpatialObject.cxx

${ITK_COMMON_EXPLICIT_SOURCES}
)

add_library(ITKSpatialObjects ${ITKSpatialObjects_SRC})
itk_module_link_dependencies()
itk_module_target(ITKSpatialObjects)
