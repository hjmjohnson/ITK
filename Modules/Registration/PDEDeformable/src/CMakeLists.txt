if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_PDEDEFORMABLEREGISTRATION_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_PDEDEFORMABLEREGISTRATION_EXPLICIT_SOURCES "")
endif()

set(ITKPDEDeformableRegistration_SRC
${ITK_PDEDEFORMABLEREGISTRATION_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKPDEDeformableRegistration_SRC)
  add_library(ITKPDEDeformableRegistration ${ITKPDEDeformableRegistration_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKPDEDeformableRegistration)
endif()
