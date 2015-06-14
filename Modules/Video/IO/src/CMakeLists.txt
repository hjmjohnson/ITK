file(GLOB ITK_VIDEOIO_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKVideoIO_SRCS
  itkFileListVideoIO.cxx
  itkFileListVideoIOFactory.cxx
  itkVideoIOBase.cxx
  itkVideoIOFactory.cxx
  ${ITK_VIDEOIO_EXPLICIT_SOURCES}
  )

itk_module_add_library(ITKVideoIO ${ITKVideoIO_SRCS})
