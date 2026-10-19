itk_module_test()
set(
  ITKStatisticsTests
  itkExpectationMaximizationMixtureModelEstimatorTest.cxx
  itkGaussianMixtureModelComponentTest.cxx
  itkGaussianRandomSpatialNeighborSubsamplerTest.cxx
  itkImageToHistogramFilterTest2.cxx
  itkKdTreeBasedKmeansEstimatorTest.cxx
  itkKdTreeGeneratorTest.cxx
  itkKdTreeTest1.cxx
  itkKdTreeTest2.cxx
  itkKdTreeTest3.cxx
  itkListSampleTest.cxx
  itkListSampleTest.cxx
  itkSampleToHistogramFilterTest5.cxx
  itkScalarImageToHistogramGeneratorTest.cxx
  itkUniformRandomSpatialNeighborSubsamplerTest.cxx
  itkWeightedCentroidKdTreeGeneratorTest1.cxx
  itkWeightedCentroidKdTreeGeneratorTest8.cxx
  itkWeightedCentroidKdTreeGeneratorTest9.cxx
  itkWeightedCovarianceSampleFilterTest2.cxx
  itkWeightedMeanSampleFilterTest.cxx
)

createtestdriver(ITKStatistics "${ITKStatistics-Test_LIBRARIES}" "${ITKStatisticsTests}")

set(TEMP ${ITK_TEST_OUTPUT_DIR})

itk_add_test(
  NAME itkExpectationMaximizationMixtureModelEstimatorTest
  COMMAND
    ITKStatisticsTestDriver
    itkExpectationMaximizationMixtureModelEstimatorTest
    DATA{${ITK_DATA_ROOT}/Input/Statistics/TwoDimensionTwoGaussian.dat}
)
itk_add_test(
  NAME itkGaussianMixtureModelComponentTest
  COMMAND
    ITKStatisticsTestDriver
    itkGaussianMixtureModelComponentTest
    DATA{${ITK_DATA_ROOT}/Input/Statistics/TwoDimensionTwoGaussian.dat}
)
itk_add_test(
  NAME itkGaussianRandomSpatialNeighborSubsamplerTest
  COMMAND
    ITKStatisticsTestDriver
    --compare
    DATA{Baseline/itkGaussianRandomSubsamplingTest.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkGaussianRandomSubsamplingTest.mha
    itkGaussianRandomSpatialNeighborSubsamplerTest
    ${ITK_TEST_OUTPUT_DIR}/itkGaussianRandomSubsamplingTest.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkGaussianRandomSubsamplingTest.mha
)
itk_add_test(
  NAME itkKdTreeBasedKmeansEstimatorTest
  COMMAND
    ITKStatisticsTestDriver
    itkKdTreeBasedKmeansEstimatorTest
    DATA{${ITK_DATA_ROOT}/Input/Statistics/TwoDimensionTwoGaussian.dat}
    1
    28.54746
    0.07
    0
)
itk_add_test(
  NAME itkKdTreeGeneratorTest
  COMMAND
    ITKStatisticsTestDriver
    itkKdTreeGeneratorTest
    DATA{${ITK_DATA_ROOT}/Input/Statistics/TwoDimensionTwoGaussian.dat}
)

itk_add_test(
  NAME itkKdTreeTest1
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest1.txt
    itkKdTreeTest1
    100
    100
    1
    ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest1_100.dot
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest1.txt
)
set_tests_properties(
  itkKdTreeTest1
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest1.txt
)

itk_add_test(
  NAME itkKdTreeTest2
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest2.txt
    itkKdTreeTest2
    DATA{${ITK_DATA_ROOT}/Input/pointsForKdTree.txt}
    1
    ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest2.dot
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest2.txt
)
set_tests_properties(
  itkKdTreeTest2
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest2.txt
)

itk_add_test(
  NAME itkKdTreeTest3
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest3.txt
    itkKdTreeTest2
    DATA{${ITK_DATA_ROOT}/Input/pointsForKdTree2.txt}
    1
    ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest3.dot
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest3.txt
)
set_tests_properties(
  itkKdTreeTest3
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest3.txt
)

itk_add_test(
  NAME itkKdTreeTest4
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest4.txt
    itkKdTreeTest1
    1000
    1000
    1
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest4.txt
)
set_tests_properties(
  itkKdTreeTest4
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest4.txt
)

itk_add_test(
  NAME itkKdTreeTest5
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest5.txt
    itkKdTreeTest1
    1000
    1000
    2
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest5.txt
)
set_tests_properties(
  itkKdTreeTest5
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest5.txt
)

itk_add_test(
  NAME itkKdTreeTest6
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest6.txt
    itkKdTreeTest1
    1000
    1000
    3
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest6.txt
)
set_tests_properties(
  itkKdTreeTest6
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest6.txt
)

itk_add_test(
  NAME itkKdTreeTest7
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest7.txt
    itkKdTreeTest1
    1000
    1000
    5
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest7.txt
)
set_tests_properties(
  itkKdTreeTest7
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest7.txt
)

itk_add_test(
  NAME itkKdTreeTest8
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest8.txt
    itkKdTreeTest1
    1000
    1000
    10
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest8.txt
)
set_tests_properties(
  itkKdTreeTest8
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest8.txt
)

itk_add_test(
  NAME itkKdTreeTest9
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest9.txt
    itkKdTreeTest1
    1000
    1000
    20
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest9.txt
)
set_tests_properties(
  itkKdTreeTest9
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest9.txt
)

itk_add_test(
  NAME itkKdTreeTest10
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest10.txt
    itkKdTreeTest1
    1000
    1000
    100
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest10.txt
)
set_tests_properties(
  itkKdTreeTest10
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest10.txt
)

itk_add_test(
  NAME itkKdTreeTest11
  COMMAND
    ITKStatisticsTestDriver
    --redirectOutput
    ${TEMP}/itkKdTreeTest11.txt
    itkKdTreeTest3
    1000
    100
    20
    16
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkKdTreeTest11.txt
)
set_tests_properties(
  itkKdTreeTest11
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkKdTreeTest11.txt
)

#
#  The following tests generate graphical plots of the KdTree organization.
#  They are very helpful for debugging and verification purposes, but not so
#  much for regression testing. They need the "dot" tool that is part of the
#  Graphviz package. The dot executable is found as part of the process of
#  configuring the Doxygen documentation. Therefore, to enable these tests
#  below, you must enable BUILD_DOXYGEN and ITK_BUILD_DOCUMENTATION.
#
if(DOXYGEN_DOT_EXECUTABLE)
  itk_add_test(
    NAME itkKdTreeTest1Plot
    COMMAND
      ${DOXYGEN_DOT_EXECUTABLE}
      -Tpng
      -o
      ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest1_100.png
      ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest1_100.dot
    ITK_REMOVE_TEMPORARY_TEST_FILES
      ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest1_100.png
  )
  set_tests_properties(
    itkKdTreeTest1Plot
    PROPERTIES
      DEPENDS
        itkKdTreeTest1
  )
  itk_add_test(
    NAME itkKdTreeTest2Plot
    COMMAND
      ${DOXYGEN_DOT_EXECUTABLE}
      -Tpng
      -o
      ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest2.png
      ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest2.dot
    ITK_REMOVE_TEMPORARY_TEST_FILES
      ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest2.png
  )
  set_tests_properties(
    itkKdTreeTest2Plot
    PROPERTIES
      DEPENDS
        itkKdTreeTest2
  )
  itk_add_test(
    NAME itkKdTreeTest3Plot
    COMMAND
      ${DOXYGEN_DOT_EXECUTABLE}
      -Tpng
      -o
      ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest3.png
      ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest3.dot
    ITK_REMOVE_TEMPORARY_TEST_FILES
      ${ITK_TEST_OUTPUT_DIR}/itkKdTreeTest3.png
  )
  set_tests_properties(
    itkKdTreeTest3Plot
    PROPERTIES
      DEPENDS
        itkKdTreeTest3
  )
endif()

itk_add_test(
  NAME itkWeightedCentroidKdTreeGeneratorTest1
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedCentroidKdTreeGeneratorTest1
    1000
    1000
    1
)
itk_add_test(
  NAME itkWeightedCentroidKdTreeGeneratorTest2
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedCentroidKdTreeGeneratorTest1
    1000
    1000
    2
)
itk_add_test(
  NAME itkWeightedCentroidKdTreeGeneratorTest3
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedCentroidKdTreeGeneratorTest1
    1000
    1000
    3
)
itk_add_test(
  NAME itkWeightedCentroidKdTreeGeneratorTest4
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedCentroidKdTreeGeneratorTest1
    1000
    1000
    5
)
itk_add_test(
  NAME itkWeightedCentroidKdTreeGeneratorTest5
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedCentroidKdTreeGeneratorTest1
    1000
    1000
    10
)
itk_add_test(
  NAME itkWeightedCentroidKdTreeGeneratorTest6
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedCentroidKdTreeGeneratorTest1
    1000
    1000
    20
)
itk_add_test(
  NAME itkWeightedCentroidKdTreeGeneratorTest7
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedCentroidKdTreeGeneratorTest1
    1000
    1000
    100
)
itk_add_test(
  NAME itkWeightedCentroidKdTreeGeneratorTest8
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedCentroidKdTreeGeneratorTest8
    1000
    1000
    1
)
itk_add_test(
  NAME itkWeightedCentroidKdTreeGeneratorTest9
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedCentroidKdTreeGeneratorTest9
    1000
    1000
    1
)
itk_add_test(
  NAME itkWeightedCovarianceSampleFilterTest2
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedCovarianceSampleFilterTest2
)
itk_add_test(
  NAME itkWeightedMeanSampleFilterTest
  COMMAND
    ITKStatisticsTestDriver
    itkWeightedMeanSampleFilterTest
)
itk_add_test(
  NAME itkListSampleTest1
  COMMAND
    ITKStatisticsTestDriver
    itkListSampleTest
    1
)
itk_add_test(
  NAME itkListSampleTest2
  COMMAND
    ITKStatisticsTestDriver
    itkListSampleTest
    5
)
itk_add_test(
  NAME itkListSampleTest3
  COMMAND
    ITKStatisticsTestDriver
    itkListSampleTest
    10
)
itk_add_test(
  NAME itkListSampleTest4
  COMMAND
    ITKStatisticsTestDriver
    itkListSampleTest
    100
)
itk_add_test(
  NAME itkSampleToHistogramFilterTest5
  COMMAND
    ITKStatisticsTestDriver
    itkSampleToHistogramFilterTest5
    DATA{${ITK_DATA_ROOT}/Input/VisibleWomanEyeSlice.png}
)
itk_add_test(
  NAME itkUniformRandomSpatialNeighborSubsamplerTest
  COMMAND
    ITKStatisticsTestDriver
    --compare
    DATA{Baseline/itkUniformRandomSubsamplingTest.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkUniformRandomSubsamplingTest.mha
    itkUniformRandomSpatialNeighborSubsamplerTest
    0
    ${ITK_TEST_OUTPUT_DIR}/itkUniformRandomSubsamplingTest.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkUniformRandomSubsamplingTest.mha
)
itk_add_test(
  NAME itkImageToHistogramFilterTest2
  COMMAND
    ITKStatisticsTestDriver
    itkImageToHistogramFilterTest2
    DATA{${ITK_DATA_ROOT}/Input/VisibleWomanEyeSlice.png}
    ${ITK_TEST_OUTPUT_DIR}/itkImageToHistogramFilterTest2.txt
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkImageToHistogramFilterTest2.txt
)
itk_add_test(
  NAME itkImageToHistogramFilterTest2_Auto
  COMMAND
    ITKStatisticsTestDriver
    itkImageToHistogramFilterTest2
    DATA{${ITK_DATA_ROOT}/Input/VisibleWomanEyeSlice.png}
    ${ITK_TEST_OUTPUT_DIR}/itkImageToHistogramFilterTest2_Auto.txt
    1
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkImageToHistogramFilterTest2_Auto.txt
)
itk_add_test(
  NAME itkScalarImageToHistogramGeneratorTest
  COMMAND
    ITKStatisticsTestDriver
    itkScalarImageToHistogramGeneratorTest
    DATA{${ITK_DATA_ROOT}/Input/cthead1.png}
    ${ITK_TEST_OUTPUT_DIR}/itkScalarImageToHistogramGeneratorTest.txt
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkScalarImageToHistogramGeneratorTest.txt
)

set(
  ITKStatisticsGTests
  itkChiSquareDistributionGTest.cxx
  itkCovarianceSampleFilterGTest.cxx
  itkCovarianceSampleFilterGTest2.cxx
  itkCovarianceSampleFilterGTest3.cxx
  itkDecisionRuleGTest.cxx
  itkDenseFrequencyContainer2GTest.cxx
  itkDistanceMetricGTest.cxx
  itkDistanceMetricGTest2.cxx
  itkDistanceToCentroidMembershipFunctionGTest.cxx
  itkEuclideanDistanceMetricGTest.cxx
  itkEuclideanSquareDistanceMetricGTest.cxx
  itkGaussianDistributionGTest.cxx
  itkGaussianMembershipFunctionGTest.cxx
  itkHistogramGTest.cxx
  itkHistogramToTextureFeaturesFilterGTest.cxx
  itkHistogramToTextureFeaturesFilterNaNGTest.cxx
  itkImageToHistogramFilterGTest.cxx
  itkImageToListSampleAdaptorGTest.cxx
  itkImageToListSampleAdaptorGTest2.cxx
  itkImageToListSampleFilterGTest.cxx
  itkImageToListSampleFilterGTest2.cxx
  itkImageToListSampleFilterGTest3.cxx
  itkJointDomainImageToListSampleAdaptorGTest.cxx
  itkKalmanLinearEstimatorGTest.cxx
  itkKdTreeGTest.cxx
  itkKdTreeGTestSamplePoints.cxx
  itkMahalanobisDistanceMetricGTest.cxx
  itkManhattanDistanceMetricGTest.cxx
  itkMaximumDecisionRuleGTest.cxx
  itkMaximumRatioDecisionRuleGTest.cxx
  itkMeanSampleFilterGTest.cxx
  itkMeanSampleFilterGTest2.cxx
  itkMeanSampleFilterGTest3.cxx
  itkMeasurementVectorTraitsGTest.cxx
  itkMembershipFunctionBaseGTest.cxx
  itkMembershipFunctionBaseGTest2.cxx
  itkMembershipSampleGTest1.cxx
  itkMembershipSampleGTest2.cxx
  itkMembershipSampleGTest3.cxx
  itkMembershipSampleGTest4.cxx
  itkMinimumDecisionRuleGTest.cxx
  itkMixtureModelComponentBaseGTest.cxx
  itkNeighborhoodSamplerGTest1.cxx
  itkNormalVariateGeneratorGTest1.cxx
  itkPointSetToListSampleAdaptorGTest.cxx
  itkProbabilityDistributionGTest.cxx
  itkRandomVariateGeneratorBaseGTest.cxx
  itkSampleGTest.cxx
  itkSampleGTest2.cxx
  itkSampleGTest3.cxx
  itkSampleGTest4.cxx
  itkSampleToHistogramFilterGTest.cxx
  itkSampleToHistogramFilterGTest2.cxx
  itkSampleToHistogramFilterGTest3.cxx
  itkSampleToHistogramFilterGTest6.cxx
  itkSampleToHistogramFilterGTest7.cxx
  itkSampleToSubsampleFilterGTest1.cxx
  itkScalarImageToCooccurrenceListSampleFilterGTest.cxx
  itkScalarImageToCooccurrenceMatrixFilterGTest.cxx
  itkScalarImageToCooccurrenceMatrixFilterGTest2.cxx
  itkScalarImageToRunLengthFeaturesFilterGTest.cxx
  itkScalarImageToRunLengthMatrixFilterGTest.cxx
  itkScalarImageToTextureFeaturesFilterGTest.cxx
  itkSparseFrequencyContainer2GTest.cxx
  itkSpatialNeighborSubsamplerGTest.cxx
  itkStandardDeviationPerComponentSampleFilterGTest.cxx
  itkStatisticsAlgorithmGTest.cxx
  itkStatisticsAlgorithmGTest2.cxx
  itkStatisticsTypesGTest.cxx
  itkSubsampleGTest.cxx
  itkSubsampleGTest2.cxx
  itkSubsampleGTest3.cxx
  itkTDistributionGTest.cxx
  itkUniformRandomSpatialNeighborSubsamplerGTest.cxx
  itkVectorContainerToListSampleAdaptorGTest.cxx
  itkWeightedCovarianceSampleFilterGTest.cxx
)
# There is a bug in VS2008, Release build that causes this test to fail.
if(NOT MSVC90)
  list(APPEND ITKStatisticsGTests itkSampleToHistogramFilterGTest4.cxx)
endif()
creategoogletestdriver(ITKStatistics "${ITKStatistics-Test_LIBRARIES}" "${ITKStatisticsGTests}")
