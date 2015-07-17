if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_COMMON_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_COMMON_EXPLICIT_SOURCES "")
endif()

set(ITKIOMesh_SRC
  itkMeshFileReaderException.cxx
  itkBYUMeshIO.cxx
  itkBYUMeshIOFactory.cxx
  itkFreeSurferAsciiMeshIO.cxx
  itkFreeSurferAsciiMeshIOFactory.cxx
  itkFreeSurferBinaryMeshIO.cxx
  itkFreeSurferBinaryMeshIOFactory.cxx
  itkGiftiMeshIO.cxx
  itkGiftiMeshIOFactory.cxx
  itkMeshIOBase.cxx
  itkMeshIOFactory.cxx
  itkOBJMeshIO.cxx
  itkOBJMeshIOFactory.cxx
  itkOFFMeshIO.cxx
  itkOFFMeshIOFactory.cxx
  itkVTKPolyDataMeshIO.cxx
  itkVTKPolyDataMeshIOFactory.cxx

  ${ITK_COMMON_EXPLICIT_SOURCES}
)

add_library(ITKIOMesh ${ITK_LIBRARY_BUILD_TYPE} ${ITKIOMesh_SRC})
itk_module_link_dependencies()
itk_module_target(ITKIOMesh)
