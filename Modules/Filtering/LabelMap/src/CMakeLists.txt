set(ITKLabelMap_SRCS
  itkGeometryUtilities.cxx
  itkLabelMapExplicit.cxx
  )
### generating libraries
itk_module_add_library( ITKLabelMap ${ITKLabelMap_SRCS})
