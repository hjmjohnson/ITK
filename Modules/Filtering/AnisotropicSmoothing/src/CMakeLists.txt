if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_ANISOTROPICSMOOTHING_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_ANISOTROPICSMOOTHING_EXPLICIT_SOURCES "")
endif()

set(ITKAnisotropicSmoothing_SRC
${ITK_ANISOTROPICSMOOTHING_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKAnisotropicSmoothing_SRC)
  add_library(ITKAnisotropicSmoothing ${ITKAnisotropicSmoothing_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKAnisotropicSmoothing)
endif()
