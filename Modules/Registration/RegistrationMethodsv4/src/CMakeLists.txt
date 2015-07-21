if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_REGISTRATIONMETHODSv4_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_REGISTRATIONMETHODSv4_EXPLICIT_SOURCES "")
endif()

set(ITKRegistrationMethodsv4_SRC
${ITK_REGISTRATIONMETHODSv4_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKRegistrationMethodsv4_SRC)
  add_library(ITKRegistrationMethodsv4 ${ITKRegistrationMethodsv4_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKRegistrationMethodsv4)
endif()
