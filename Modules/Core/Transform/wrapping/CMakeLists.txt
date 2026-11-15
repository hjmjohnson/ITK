itk_wrap_module(ITKTransform)

set(
  WRAPPER_SUBMODULE_ORDER
  itkCompositeTransform
  itkTransformBase
  itkMatrixOffsetTransformBase
  itkMultiTransform
  itkVersorTransform
  itkVersorRigid3DTransform
  itkAffineTransform
)
itk_auto_load_and_end_wrap_submodules()
