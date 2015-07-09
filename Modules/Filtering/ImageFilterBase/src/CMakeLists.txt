if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_IMAGEFILTERBASE_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_IMAGEFILTERBASE_EXPLICIT_SOURCES "")
endif()

set(ITKImageFilterBase_SRC
${ITK_IMAGEFILTERBASE_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKImageFilterBase_SRC)
  add_library(ITKImageFilterBase ${ITKImageFilterBase_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKImageFilterBase)
endif()
