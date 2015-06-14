if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_MESHBASE_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_MESHBASE_EXPLICIT_SOURCES "")
endif()
set(ITKIOMeshBase_SRCS
  itkMeshFileReaderException.cxx
  itkMeshFileWriterException.cxx
  itkMeshIOBase.cxx
  itkMeshIOFactory.cxx

  ${ITK_MESHBASE_EXPLICIT_SOURCES}
)

itk_module_add_library(ITKIOMeshBase ${ITKIOMeshBase_SRCS})
