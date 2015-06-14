set(DOCUMENTATION "This module contains classes for reading and writing
SpatialObjects as opposed to general images.  The SpatialObjects are written in
<a
href=\"http://www.vtk.org/Wiki/MetaIO/Documentation#Spatial_Objects\">MetaIO</a>
format.")


itk_module(ITKIOSpatialObjects
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKSpatialObjects
  PRIVATE_DEPENDS
    ITKIOXML
    ITKMesh
  TEST_DEPENDS
    ITKTestKernel
    ITKSpatialObjects
    ITKIOXML
    ITKMetaIO
    ITKMesh
  DESCRIPTION
    "${DOCUMENTATION}"
)
