if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_DISTANCEMAP_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_DISTANCEMAP_EXPLICIT_SOURCES "")
endif()

set(ITKDistanceMap_SRC
${ITK_DISTANCEMAP_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKDistanceMap_SRC)
  add_library(ITKDistanceMap ${ITKDistanceMap_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKDistanceMap)
endif()
