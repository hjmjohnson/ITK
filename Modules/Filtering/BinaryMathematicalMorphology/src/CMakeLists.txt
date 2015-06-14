if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_BINARYMATHEMATICALMORPHOLOGY_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_BINARYMATHEMATICALMORPHOLOGY_EXPLICIT_SOURCES "")
endif()

set(ITKBinaryMathematicalMorphology_SRC
${ITK_BINARYMATHEMATICALMORPHOLOGY_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKBinaryMathematicalMorphology_SRC)
  add_library(ITKBinaryMathematicalMorphology ${ITKBinaryMathematicalMorphology_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKBinaryMathematicalMorphology)
endif()
