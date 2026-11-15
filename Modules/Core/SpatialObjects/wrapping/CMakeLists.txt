itk_wrap_module(ITKSpatialObjects)

set(
  WRAPPER_SUBMODULE_ORDER
  itkSpatialObjectBase
  itkImageSpatialObject
  itkImageMaskSpatialObject
)
itk_auto_load_and_end_wrap_submodules()
