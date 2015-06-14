set(DOCUMENTATION "This module contains an ImageIO class for reading LSM (Zeiss)
images LSM is a line of confocal laser scanning microscopes produced by the
Zeiss company. LSM files are essentially extensions of the TIFF multiple image
stack file format.")

itk_module(ITKIOLSM
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKIOTIFF
  ENABLE_SHARED
  PRIVATE_DEPENDS
    ITKIOImageBase
    ITKKWIML
    ITKTIFF
  TEST_DEPENDS
    ITKTestKernel
    ITKIOTIFF
  FACTORY_NAMES
    ImageIO::LSM
  DESCRIPTION
    "${DOCUMENTATION}"
)
