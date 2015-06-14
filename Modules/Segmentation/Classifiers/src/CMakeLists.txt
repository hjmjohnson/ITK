if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_CLASSIFIERS_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_CLASSIFIERS_EXPLICIT_SOURCES "")
endif()

set(ITKClassifiers_SRC
${ITK_CLASSIFIERS_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKClassifiers_SRC)
  add_library(ITKClassifiers ${ITKClassifiers_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKClassifiers)
endif()
