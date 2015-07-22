if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_VORONOI_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_VORONOI_EXPLICIT_SOURCES "")
endif()

set(ITKVoronoi_SRC
${ITK_VORONOI_EXPLICIT_SOURCES}
)

# only add library if it will have object files;
# otherwise it causes a build error.
if(ITKVoronoi_SRC)
  add_library(ITKVoronoi ${ITKVoronoi_SRC})
  itk_module_link_dependencies()
  itk_module_target(ITKVoronoi)
endif()
