if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IOIMAGEBASE_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IOIMAGEBASE_EXPLICIT_SOURCES "")
endif()

set(ITKIOImageBase_SRC
itkImageSeriesWriter.cxx
itkImageFileReaderException.cxx
itkImageFileWriter.cxx
itkArchetypeSeriesFileNames.cxx
itkImageIOFactory.cxx
itkIOCommon.cxx
itkNumericSeriesFileNames.cxx
itkImageIOBase.cxx
itkRegularExpressionSeriesFileNames.cxx
itkStreamingImageIOBase.cxx

${ITK_IOIMAGEBASE_EXPLICIT_SOURCES}
)

add_library(ITKIOImageBase ${ITK_LIBRARY_BUILD_TYPE} ${ITKIOImageBase_SRC})
itk_module_link_dependencies()
itk_module_target(ITKIOImageBase)
