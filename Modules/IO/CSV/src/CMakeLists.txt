file(GLOB ITK_ITKIOCSV_EXPLICIT_SOURCES "*Explicit.cxx")
set(ITKIOCSV_SRCS
  itkCSVFileReaderBase.cxx
  ${ITK_ITKIOCSV_EXPLICIT_SOURCES}
  )

itk_module_add_library(ITKIOCSV ${ITKIOCSV_SRCS})
