itk_module_test()
set(
  ITKImageIntensityTests
  itkAddImageFilterTest2.cxx
  itkAndImageFilterTest.cxx
  itkBoundedReciprocalImageFilterTest.cxx
  itkConstrainedValueAdditionImageFilterTest.cxx
  itkDiscreteGaussianDerivativeImageFunctionTest.cxx
  itkDiscreteGradientMagnitudeGaussianImageFunctionTest.cxx
  itkDiscreteHessianGaussianImageFunctionTest.cxx
  itkInvertIntensityImageFilterTest.cxx
  itkMagnitudeAndPhaseToComplexImageFilterTest.cxx
  itkMatrixIndexSelectionImageFilterTest.cxx
  itkModulusImageFilterTest.cxx
  itkNormalizeImageFilterTest.cxx
  itkOrImageFilterTest.cxx
  itkPolylineMask2DImageFilterTest.cxx
  itkPolylineMaskImageFilterTest.cxx
  itkPromoteDimensionImageTest.cxx
  itkRescaleIntensityImageFilterTest.cxx
  itkRGBToLuminanceImageFilterAndAdaptorTest.cxx
  itkRGBToVectorAdaptImageFilterTest.cxx
  itkShiftScaleImageFilterTest.cxx
  itkSigmoidImageFilterTest.cxx
  itkSinImageFilterAndAdaptorTest.cxx
  itkSqrtImageFilterAndAdaptorTest.cxx
  itkSubtractImageFilterTest.cxx
  itkSymmetricEigenAnalysisImageFilterTest.cxx
  itkTanImageFilterAndAdaptorTest.cxx
  itkTernaryMagnitudeImageFilterTest.cxx
  itkTernaryMagnitudeSquaredImageFilterTest.cxx
  itkTernaryOperatorImageFilterTest.cxx
  itkVectorIndexSelectionCastImageFilterTest.cxx
  itkVectorMagnitudeImageFilterTest.cxx
  itkVectorRescaleIntensityImageFilterTest.cxx
  itkVectorToRGBImageAdaptorTest.cxx
  itkWeightedAddImageFilterTest.cxx
  itkXorImageFilterTest.cxx
)

if(NOT ITK_LEGACY_REMOVE)
  list(APPEND ITKImageIntensityTests itkVectorExpandImageFilterTest.cxx)
endif()

# Disable optimization on the tests below to avoid possible
# optimization bugs in some compilers. This option will appear on the
# command line after any other optimization flag (including those from
# CMAKE_CXX_FLAGS) which means that on gcc, MSVC, and the Intel
# compiler, it will override any other optimization flag.
if(DEFINED ITK_CXX_DISABLE_OPTIMIZATION_FLAG)
  set_source_files_properties(
    itkClampImageFilterGTest.cxx
    PROPERTIES
      COMPILE_FLAGS
        ${ITK_CXX_DISABLE_OPTIMIZATION_FLAG}
  )
endif()

createtestdriver(ITKImageIntensity "${ITKImageIntensity-Test_LIBRARIES}" "${ITKImageIntensityTests}")

set(TEMP ${ITK_TEST_OUTPUT_DIR})

itk_add_test(
  NAME itkBoundedReciprocalImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkBoundedReciprocalImageFilterTest
    DATA{${ITK_DATA_ROOT}/Input/Gourds.png}
)
itk_add_test(
  NAME itkVectorRescaleIntensityImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkVectorRescaleIntensityImageFilterTest
)
itk_add_test(
  NAME itkTernaryMagnitudeSquaredImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkTernaryMagnitudeSquaredImageFilterTest
)
itk_add_test(
  NAME itkTernaryOperatorImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkTernaryOperatorImageFilterTest
)
itk_add_test(
  NAME itkVectorIndexSelectionCastImageFilterTest1
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/BasicFilters/itkVectorIndexSelectionCastImageFilterTest1.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkVectorIndexSelectionCastImageFilterTest1.mha
    itkVectorIndexSelectionCastImageFilterTest
    DATA{${ITK_DATA_ROOT}/Input/RGBTestImage.tif}
    ${ITK_TEST_OUTPUT_DIR}/itkVectorIndexSelectionCastImageFilterTest1.mha
    0
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkVectorIndexSelectionCastImageFilterTest1.mha
)
itk_add_test(
  NAME itkVectorIndexSelectionCastImageFilterTest2
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/BasicFilters/itkVectorIndexSelectionCastImageFilterTest2.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkVectorIndexSelectionCastImageFilterTest2.mha
    itkVectorIndexSelectionCastImageFilterTest
    DATA{${ITK_DATA_ROOT}/Input/RGBTestImage.tif}
    ${ITK_TEST_OUTPUT_DIR}/itkVectorIndexSelectionCastImageFilterTest2.mha
    1
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkVectorIndexSelectionCastImageFilterTest2.mha
)
itk_add_test(
  NAME itkVectorIndexSelectionCastImageFilterTest3
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/BasicFilters/itkVectorIndexSelectionCastImageFilterTest3.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkVectorIndexSelectionCastImageFilterTest3.mha
    itkVectorIndexSelectionCastImageFilterTest
    DATA{${ITK_DATA_ROOT}/Input/RGBTestImage.tif}
    ${ITK_TEST_OUTPUT_DIR}/itkVectorIndexSelectionCastImageFilterTest3.mha
    2
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkVectorIndexSelectionCastImageFilterTest3.mha
)
itk_add_test(
  NAME itkInvertIntensityImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/BasicFilters/InvertIntensityImageFilterTest.png}
    ${ITK_TEST_OUTPUT_DIR}/InvertIntensityImageFilterTest.png
    itkInvertIntensityImageFilterTest
    DATA{${ITK_DATA_ROOT}/Input/cthead1.png}
    ${ITK_TEST_OUTPUT_DIR}/InvertIntensityImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/InvertIntensityImageFilterTest.png
)
itk_add_test(
  NAME itkSymmetricEigenAnalysisImageFilterTestOrderByValue
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisImageFilterTestOrderByValue.png
    8e3e4221d36144133d2f6692b2ad980b
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisFixedDimensionImageFilterTestOrderByValue.png
    8e3e4221d36144133d2f6692b2ad980b
    itkSymmetricEigenAnalysisImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisImageFilterTestOrderByValue.png
    1
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisFixedDimensionImageFilterTestOrderByValue.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisImageFilterTestOrderByValue.png
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisFixedDimensionImageFilterTestOrderByValue.png
)
itk_add_test(
  NAME itkSymmetricEigenAnalysisImageFilterTestOrderByMagnitude
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisImageFilterTestOrderByMagnitude.png
    8e3e4221d36144133d2f6692b2ad980b
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisFixedDimensionImageFilterTestOrderByMagnitude.png
    8e3e4221d36144133d2f6692b2ad980b
    itkSymmetricEigenAnalysisImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisImageFilterTestOrderByMagnitude.png
    2
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisFixedDimensionImageFilterTestOrderByMagnitude.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisImageFilterTestOrderByMagnitude.png
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisFixedDimensionImageFilterTestOrderByMagnitude.png
)
# FixedDimension (with Eigen3) orders by value by default.
itk_add_test(
  NAME itkSymmetricEigenAnalysisImageFilterTestDoNotOrder
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisImageFilterTestDoNotOrder.png
    8e3e4221d36144133d2f6692b2ad980b
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisFixedDimensionImageFilterTestDoNotOrder.png
    8e3e4221d36144133d2f6692b2ad980b
    itkSymmetricEigenAnalysisImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisImageFilterTestDoNotOrder.png
    3
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisFixedDimensionImageFilterTestDoNotOrder.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisImageFilterTestDoNotOrder.png
    ${ITK_TEST_OUTPUT_DIR}/itkSymmetricEigenAnalysisFixedDimensionImageFilterTestDoNotOrder.png
)
itk_add_test(
  NAME itkAndImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkAndImageFilterTest.png
    93d46ee3d5e0c157e2b2d27977ae4d0f
    itkAndImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkAndImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkAndImageFilterTest.png
)
itk_add_test(
  NAME itkConstrainedValueAdditionImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkConstrainedValueAdditionImageFilterTest.png
    6ef609d089e93e2eed8f089f75bc67fb
    itkConstrainedValueAdditionImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkConstrainedValueAdditionImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkConstrainedValueAdditionImageFilterTest.png
)
itk_add_test(
  NAME itkAddImageFilterTest2
  COMMAND
    ITKImageIntensityTestDriver
    itkAddImageFilterTest2
    DATA{${ITK_DATA_ROOT}/Input/HeadMRVolume.mha}
    ${TEMP}/itkAddImageFilterTest2.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkAddImageFilterTest2.mha
)
itk_add_test(
  NAME itkWeightedAddImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkWeightedAddImageFilterTest
    0.4
)
itk_add_test(
  NAME itkRescaleIntensityImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkRescaleIntensityImageFilterTest
)

itk_add_test(
  NAME itkNormalizeImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --redirectOutput
    ${TEMP}/itkNormalizeImageFilterTest.txt
    itkNormalizeImageFilterTest
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkNormalizeImageFilterTest.txt
)
set_tests_properties(
  itkNormalizeImageFilterTest
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkNormalizeImageFilterTest.txt
)

itk_add_test(
  NAME itkShiftScaleImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkShiftScaleImageFilterTest
)
itk_add_test(
  NAME itkTernaryMagnitudeImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkTernaryMagnitudeImageFilterTest.png
    7f199e1363c4b754eb03cf4d0ba8d343
    itkTernaryMagnitudeImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkTernaryMagnitudeImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkTernaryMagnitudeImageFilterTest.png
)
itk_add_test(
  NAME itkMatrixIndexSelectionImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/BasicFilters/MatrixIndexSelectionImageFilterTest.png}
    ${ITK_TEST_OUTPUT_DIR}/MatrixIndexSelectionImageFilterTest.png
    itkMatrixIndexSelectionImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/MatrixIndexSelectionImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/MatrixIndexSelectionImageFilterTest.png
)
itk_add_test(
  NAME itkRGBToVectorAdaptImageFilterTest.cxx
  COMMAND
    ITKImageIntensityTestDriver
    itkRGBToVectorAdaptImageFilterTest
)
itk_add_test(
  NAME itkSqrtImageFilterAndAdaptorTest
  COMMAND
    ITKImageIntensityTestDriver
    itkSqrtImageFilterAndAdaptorTest
)
itk_add_test(
  NAME itkTanImageFilterAndAdaptorTest
  COMMAND
    ITKImageIntensityTestDriver
    itkTanImageFilterAndAdaptorTest
)
itk_add_test(
  NAME itkSigmoidImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkSigmoidImageFilterTest
)
if(NOT ITK_LEGACY_REMOVE)
  itk_add_test(
    NAME itkVectorExpandImageFilterTest
    COMMAND
      ITKImageIntensityTestDriver
      itkVectorExpandImageFilterTest
  )
endif()
itk_add_test(
  NAME itkOrImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkOrImageFilterTest.png
    817d6d96c1c07cb12bfc200134aa57ba
    itkOrImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkOrImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkOrImageFilterTest.png
)
itk_add_test(
  NAME itkRGBToLuminanceImageFilterAndAdaptorTest.cxx
  COMMAND
    ITKImageIntensityTestDriver
    itkRGBToLuminanceImageFilterAndAdaptorTest
)
itk_add_test(
  NAME itkXorImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkXorImageFilterTest.png
    3b5b9852567ef7618aac7f5f2d74ef74
    itkXorImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkXorImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkXorImageFilterTest.png
)
itk_add_test(
  NAME itkSubtractImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkSubtractImageFilterTest
)
itk_add_test(
  NAME itkVectorToRGBImageAdaptorTest
  COMMAND
    ITKImageIntensityTestDriver
    itkVectorToRGBImageAdaptorTest
)
itk_add_test(
  NAME itkSinImageFilterAndAdaptorTest
  COMMAND
    ITKImageIntensityTestDriver
    itkSinImageFilterAndAdaptorTest
)
itk_add_test(
  NAME itkPolylineMask2DImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkPolylineMask2DImageFilterTest
    DATA{${ITK_DATA_ROOT}/Input/cthead1.png}
    ${ITK_TEST_OUTPUT_DIR}/itkPolylineMask2DImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkPolylineMask2DImageFilterTest.png
)
itk_add_test(
  NAME itkPolylineMaskImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{Baseline/PolylineMaskImageFilterTest.mha}
    ${ITK_TEST_OUTPUT_DIR}/PolylineMaskImageFilterTest.mha
    itkPolylineMaskImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/PolylineMaskImageFilterTest.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/PolylineMaskImageFilterTest.mha
)
itk_add_test(
  NAME itkPromoteDimensionImageTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/BasicFilters/PromoteDimensionImageTest.mhd,PromoteDimensionImageTest.raw}
    ${ITK_TEST_OUTPUT_DIR}/PromoteDimensionImageTest.mhd
    itkPromoteDimensionImageTest
    DATA{${ITK_DATA_ROOT}/Input/VisibleWomanEyeSlice.png}
    ${ITK_TEST_OUTPUT_DIR}/PromoteDimensionImageTest.mhd
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/PromoteDimensionImageTest.{mhd,raw}
)
itk_add_test(
  NAME itkModulusImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/BasicFilters/ModulusImageFilterTest.png}
    ${ITK_TEST_OUTPUT_DIR}/ModulusImageFilterTest.png
    itkModulusImageFilterTest
    DATA{${ITK_DATA_ROOT}/Input/Spots.png}
    ${ITK_TEST_OUTPUT_DIR}/ModulusImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/ModulusImageFilterTest.png
)
itk_add_test(
  NAME itkVectorMagnitudeImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    itkVectorMagnitudeImageFilterTest
)
itk_add_test(
  NAME itkMagnitudeAndPhaseToComplexImageFilterTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{Baseline/itkMagnitudeAndPhaseToComplexImageFilterTestBaseline.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkMagnitudeAndPhaseToComplexImageFilterTest.mha
    itkMagnitudeAndPhaseToComplexImageFilterTest
    DATA{Input/itkBrainSliceComplexMagnitude.mha}
    DATA{Input/itkBrainSliceComplexPhase.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkMagnitudeAndPhaseToComplexImageFilterTest.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkMagnitudeAndPhaseToComplexImageFilterTest.mha
)
itk_add_test(
  NAME itkDiscreteHessianGaussianImageFunctionTest
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{Baseline/itkDiscreteHessianGaussianImageFunctionTest.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteHessianGaussianImageFunctionTest.mha
    itkDiscreteHessianGaussianImageFunctionTest
    DATA{${ITK_DATA_ROOT}/Input/cthead1.png}
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteHessianGaussianImageFunctionTest.mha
    2.0
    0.01
    32
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteHessianGaussianImageFunctionTest.mha
)
itk_add_test(
  NAME itkDiscreteGradientMagnitudeGaussianImageFunctionTest01
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{Baseline/itkDiscreteGradientMagnitudeGaussianImageFunctionTest01.png}
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGradientMagnitudeGaussianImageFunctionTest01.png
    itkDiscreteGradientMagnitudeGaussianImageFunctionTest
    DATA{${ITK_DATA_ROOT}/Input/cthead1.png}
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGradientMagnitudeGaussianImageFunctionTest01.png
    2.0
    0.01
    32
    0
    1
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGradientMagnitudeGaussianImageFunctionTest01.png
)
itk_add_test(
  NAME itkDiscreteGradientMagnitudeGaussianImageFunctionTest02
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGradientMagnitudeGaussianImageFunctionTest02.png
    de1904605e667018baaa3f73c5e5c220
    itkDiscreteGradientMagnitudeGaussianImageFunctionTest
    DATA{${ITK_DATA_ROOT}/Input/cthead1.png}
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGradientMagnitudeGaussianImageFunctionTest02.png
    1.5
    0.03
    64
    1
    1
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGradientMagnitudeGaussianImageFunctionTest02.png
)
itk_add_test(
  NAME itkDiscreteGradientMagnitudeGaussianImageFunctionTestUseImageSpacingOff
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGradientMagnitudeGaussianImageFunctionTestUseImageSpacingOff.png
    de1904605e667018baaa3f73c5e5c220
    itkDiscreteGradientMagnitudeGaussianImageFunctionTest
    DATA{${ITK_DATA_ROOT}/Input/cthead1.png}
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGradientMagnitudeGaussianImageFunctionTestUseImageSpacingOff.png
    1.5
    0.03
    64
    1
    0
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGradientMagnitudeGaussianImageFunctionTestUseImageSpacingOff.png
)
itk_add_test(
  NAME itkDiscreteGaussianDerivativeImageFunctionTest01
  COMMAND
    ITKImageIntensityTestDriver
    --compare
    DATA{Baseline/itkDiscreteGaussianDerivativeImageFunctionTest01.png}
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGaussianDerivativeImageFunctionTest01.png
    itkDiscreteGaussianDerivativeImageFunctionTest
    DATA{${ITK_DATA_ROOT}/Input/cthead1.png}
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGaussianDerivativeImageFunctionTest01.png
    1
    2.0
    0.01
    32
    0
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGaussianDerivativeImageFunctionTest01.png
)
itk_add_test(
  NAME itkDiscreteGaussianDerivativeImageFunctionTest02
  COMMAND
    ITKImageIntensityTestDriver
    --compare-MD5
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGaussianDerivativeImageFunctionTest02.png
    488a4bf5daa08cadb3e8b1018a3fe5c0
    itkDiscreteGaussianDerivativeImageFunctionTest
    DATA{${ITK_DATA_ROOT}/Input/cthead1.png}
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGaussianDerivativeImageFunctionTest02.png
    2
    1.5
    0.03
    16
    1
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkDiscreteGaussianDerivativeImageFunctionTest02.png
)

set(
  ITKImageIntensityGTests
  itkAbsImageFilterAndAdaptorGTest.cxx
  itkAcosImageFilterAndAdaptorGTest.cxx
  itkAdaptImageFilterGTest.cxx
  itkAdaptImageFilterGTest2.cxx
  itkAddImageAdaptorGTest.cxx
  itkAddImageFilterFrameGTest.cxx
  itkAddImageFilterGTest.cxx
  itkArithmeticOpsFunctorsTest.cxx
  itkAsinImageFilterAndAdaptorGTest.cxx
  itkAtan2ImageFilterGTest.cxx
  itkAtanImageFilterAndAdaptorGTest.cxx
  itkBinaryMagnitudeImageFilterGTest.cxx
  itkBitwiseOpsFunctorsTest.cxx
  itkClampImageFilterGTest.cxx
  itkComplexToImaginaryFilterAndAdaptorGTest.cxx
  itkComplexToModulusFilterAndAdaptorGTest.cxx
  itkComplexToPhaseFilterAndAdaptorGTest.cxx
  itkComplexToRealFilterAndAdaptorGTest.cxx
  itkCosImageFilterAndAdaptorGTest.cxx
  itkDivideImageFilterGTest.cxx
  itkDivideImageFilterGTest2.cxx
  itkDivideOrZeroOutImageFilterGTest.cxx
  itkEdgePotentialImageFilterGTest.cxx
  itkEqualGTest.cxx
  itkExpImageFilterAndAdaptorGTest.cxx
  itkExpNegativeImageFilterAndAdaptorGTest.cxx
  itkGreaterEqualGTest.cxx
  itkGreaterGTest.cxx
  itkHistogramMatchingImageFilterGTest.cxx
  itkImageAdaptorNthElementGTest.cxx
  itkIntensityWindowingImageFilterGTest.cxx
  itkLessEqualGTest.cxx
  itkLessGTest.cxx
  itkLog10ImageFilterAndAdaptorGTest.cxx
  itkLogImageFilterAndAdaptorGTest.cxx
  itkMaskedAssignImageFilterGTest.cxx
  itkMaskImageFilterGTest.cxx
  itkMaskNegatedImageFilterGTest.cxx
  itkMaximumImageFilterGTest.cxx
  itkMinimumImageFilterGTest.cxx
  itkMultiplyImageFilterGTest.cxx
  itkNaryAddImageFilterGTest.cxx
  itkNaryMaximumImageFilterGTest.cxx
  itkNormalizeToConstantImageFilterGTest.cxx
  itkNotEqualGTest.cxx
  itkNotImageFilterGTest.cxx
  itkNthElementPixelAccessorGTest2.cxx
  itkPowImageFilterGTest.cxx
  itkRoundImageFilterGTest.cxx
  itkSquareImageFilterGTest.cxx
)

if(MSVC)
  # disable false warning about floating division by zero
  # Floating division by zero is defined unlike integer division
  set_source_files_properties(
    itkArithmeticOpsFunctorsTest.cxx
    PROPERTIES
      COMPILE_FLAGS
        -wd4723
  )
endif()

creategoogletestdriver(ITKImageIntensity "${ITKImageIntensity-Test_LIBRARIES}" "${ITKImageIntensityGTests}")
