if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_VIDEOIO_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_VIDEOIO_EXPLICIT_SOURCES "")
endif()

set(ITKVideoIO_SRC
itkFileListVideoIO.cxx
itkFileListVideoIOFactory.cxx
itkVideoIOBase.cxx
itkVideoIOFactory.cxx

${ITK_VIDEOIO_EXPLICIT_SOURCES}
)

add_library(ITKVideoIO ${ITKVideoIO_SRC})
itk_module_link_dependencies()
itk_module_target(ITKVideoIO)
