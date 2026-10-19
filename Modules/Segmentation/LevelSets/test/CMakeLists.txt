itk_module_test()
set(
  ITKLevelSetsTests
  itkBinaryMaskToNarrowBandPointSetFilterTest.cxx
  itkCollidingFrontsImageFilterTest.cxx
  itkLevelSetNeighborhoodExtractorTest.cxx
  itkNarrowBandCurvesLevelSetImageFilterTest.cxx
  itkParallelSparseFieldLevelSetImageFilterTest.cxx
  itkShapePriorMAPCostFunctionTest.cxx
  itkShapePriorSegmentationLevelSetFunctionTest.cxx
  itkSparseFieldFourthOrderLevelSetImageFilterTest.cxx
  itkThresholdSegmentationLevelSetImageFilterTest.cxx
  itkUnsharpMaskLevelSetImageFilterTest.cxx
  itkVectorThresholdSegmentationLevelSetImageFilterTest.cxx
)

createtestdriver(ITKLevelSets "${ITKLevelSets-Test_LIBRARIES}" "${ITKLevelSetsTests}")

set(
  ITKLevelSetsGTests
  itkAnisotropicFourthOrderLevelSetImageFilterGTest.cxx
  itkCannySegmentationLevelSetImageFilterGTest.cxx
  itkCurvesLevelSetImageFilterGTest.cxx
  itkCurvesLevelSetImageFilterZeroSigmaGTest.cxx
  itkExtensionVelocitiesImageFilterGTest.cxx
  itkGeodesicActiveContourLevelSetImageFilterGTest.cxx
  itkGeodesicActiveContourLevelSetImageFilterZeroSigmaGTest.cxx
  itkGeodesicActiveContourShapePriorLevelSetImageFilterGTest.cxx
  itkGeodesicActiveContourShapePriorLevelSetImageFilterGTest_2.cxx
  itkImplicitManifoldNormalVectorFilterGTest.cxx
  itkIsotropicFourthOrderLevelSetImageFilterGTest.cxx
  itkLaplacianSegmentationLevelSetImageFilterGTest.cxx
  itkLevelSetFunctionGTest.cxx
  itkLevelSetNeighborhoodExtractorGTest.cxx
  itkLevelSetVelocityNeighborhoodExtractorGTest.cxx
  itkNarrowBandThresholdSegmentationLevelSetImageFilterGTest.cxx
  itkParallelSparseFieldLevelSetImageFilterRobustnessGTest.cxx
  itkReinitializeLevelSetImageFilterGTest.cxx
  itkShapeDetectionLevelSetImageFilterGTest.cxx
)
creategoogletestdriver(ITKLevelSets "${ITKLevelSets-Test_LIBRARIES}" "${ITKLevelSetsGTests}")

itk_add_test(
  NAME itkThresholdSegmentationLevelSetImageFilterTest
  COMMAND
    ITKLevelSetsTestDriver
    itkThresholdSegmentationLevelSetImageFilterTest
)
itk_add_test(
  NAME itkVectorThresholdSegmentationLevelSetImageFilterTest
  COMMAND
    ITKLevelSetsTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/Algorithms/VectorThresholdSegmentationLevelSetImageFilterTest.png,:}
    ${ITK_TEST_OUTPUT_DIR}/VectorThresholdSegmentationLevelSetImageFilterTest.png
    --compareNumberOfPixelsTolerance
    55
    itkVectorThresholdSegmentationLevelSetImageFilterTest
    DATA{${ITK_DATA_ROOT}/Input/VisibleWomanEyeSliceInitialLevelSet.png}
    DATA{${ITK_DATA_ROOT}/Input/VisibleWomanEyeSlice.png}
    ${ITK_TEST_OUTPUT_DIR}/VectorThresholdSegmentationLevelSetImageFilterTest.png
    5.0
    50
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/VectorThresholdSegmentationLevelSetImageFilterTest.png
)
itk_add_test(
  NAME itkParallelSparseFieldLevelSetImageFilterTest
  COMMAND
    ITKLevelSetsTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/BasicFilters/ParallelSparseFieldLevelSetImageFilterTest.mha}
    ${ITK_TEST_OUTPUT_DIR}/ParallelSparseFieldLevelSetImageFilterTest.mha
    itkParallelSparseFieldLevelSetImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/ParallelSparseFieldLevelSetImageFilterTest.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/ParallelSparseFieldLevelSetImageFilterTest.mha
)
itk_add_test(
  NAME itkNarrowBandCurvesLevelSetImageFilterTest1
  COMMAND
    ITKLevelSetsTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/Algorithms/itkNarrowBandCurvesLevelSetImageFilterTest.png}
    ${ITK_TEST_OUTPUT_DIR}/itkNarrowBandCurvesLevelSetImageFilterTest.png
    itkNarrowBandCurvesLevelSetImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkNarrowBandCurvesLevelSetImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkNarrowBandCurvesLevelSetImageFilterTest.png
)
itk_add_test(
  NAME itkCollidingFrontsImageFilterTest
  COMMAND
    ITKLevelSetsTestDriver
    itkCollidingFrontsImageFilterTest
    -1e-6
    1
    1
)
itk_add_test(
  NAME itkLevelSetNeighborhoodExtractorTest
  COMMAND
    ITKLevelSetsTestDriver
    itkLevelSetNeighborhoodExtractorTest
)
itk_add_test(
  NAME itkShapePriorMAPCostFunctionTest
  COMMAND
    ITKLevelSetsTestDriver
    itkShapePriorMAPCostFunctionTest
)
itk_add_test(
  NAME itkSparseFieldFourthOrderLevelSetImageFilterTest
  COMMAND
    ITKLevelSetsTestDriver
    itkSparseFieldFourthOrderLevelSetImageFilterTest
)
itk_add_test(
  NAME itkShapePriorSegmentationLevelSetFunctionTest
  COMMAND
    ITKLevelSetsTestDriver
    itkShapePriorSegmentationLevelSetFunctionTest
)
itk_add_test(
  NAME itkUnsharpMaskLevelSetImageFilterTest
  COMMAND
    ITKLevelSetsTestDriver
    itkUnsharpMaskLevelSetImageFilterTest
)
itk_add_test(
  NAME itkBinaryMaskToNarrowBandPointSetFilterTest
  COMMAND
    ITKLevelSetsTestDriver
    itkBinaryMaskToNarrowBandPointSetFilterTest
    5.0
)
