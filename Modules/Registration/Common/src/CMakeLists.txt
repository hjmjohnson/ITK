if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_RegistrationCommon_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_RegistrationCommon_EXPLICIT_SOURCES "")
endif()

set(ITKRegistrationCommon_SRC
${ITK_RegistrationCommon_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKRegistrationCommon_SRC)
  add_library(ITKRegistrationCommon ${ITKRegistrationCommon_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKRegistrationCommon)
endif()
