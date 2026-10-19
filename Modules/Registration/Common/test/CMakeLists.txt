itk_module_test()
set(
  ITKRegistrationCommonTests
  itkBlockMatchingImageFilterTest.cxx
  itkEuclideanDistancePointMetricTest.cxx
  itkImageRegistrationMethodTest_14.cxx
  itkImageRegistrationMethodTest_16.cxx
  itkImageRegistrationMethodTest_4.cxx
  itkImageRegistrationMethodTest_5.cxx
  itkImageRegistrationMethodTest_6.cxx
  itkImageRegistrationMethodTest_7.cxx
  itkImageRegistrationMethodTest_8.cxx
  itkImageRegistrationMethodTest_9.cxx
  itkImageToSpatialObjectRegistrationTest.cxx
  itkKappaStatisticImageToImageMetricTest.cxx
  itkKullbackLeiblerCompareHistogramImageToImageMetricTest.cxx
  itkLandmarkBasedTransformInitializerTest.cxx
  itkMatchCardinalityImageToImageMetricTest.cxx
  itkMattesMutualInformationImageToImageMetricTest.cxx
  itkMeanReciprocalSquareDifferenceImageMetricTest.cxx
  itkMeanReciprocalSquareDifferencePointSetToImageMetricTest.cxx
  itkMeanSquaresHistogramImageToImageMetricTest.cxx
  itkMeanSquaresImageMetricTest.cxx
  itkMeanSquaresPointSetToImageMetricTest.cxx
  itkMultiResolutionImageRegistrationMethodTest.cxx
  itkMultiResolutionImageRegistrationMethodTest_1.cxx
  itkMultiResolutionImageRegistrationMethodTest_2.cxx
  itkMultiResolutionPyramidImageFilterTest.cxx
  itkMutualInformationHistogramImageToImageMetricTest.cxx
  itkMutualInformationMetricTest.cxx
  itkNormalizedCorrelationImageMetricTest.cxx
  itkNormalizedCorrelationPointSetToImageMetricTest.cxx
  itkNormalizedMutualInformationHistogramImageToImageMetricTest.cxx
  itkPointSetToImageRegistrationTest.cxx
  itkPointSetToPointSetRegistrationTest.cxx
  itkPointSetToSpatialObjectDemonsRegistrationTest.cxx
  itkPointsLocatorTest.cxx
  itkRecursiveMultiResolutionPyramidImageFilterTest.cxx
)

createtestdriver(ITKRegistrationCommon "${ITKRegistrationCommon-Test_LIBRARIES}" "${ITKRegistrationCommonTests}")

set(TEMP ${ITK_TEST_OUTPUT_DIR})

itk_add_test(
  NAME itkMultiResolutionImageRegistrationMethodTest_1
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMultiResolutionImageRegistrationMethodTest_1
)
itk_add_test(
  NAME itkMultiResolutionImageRegistrationMethodTest_2
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMultiResolutionImageRegistrationMethodTest_2
)

#Temporarily output full results for debugging of experimental builds
#itk_add_test(NAME itkImageRegistrationMethodTest_14
#      COMMAND ITKRegistrationCommonTestDriver --redirectOutput ${TEMP}/#itkImageRegistrationMethodTest_14.txt
#    itkImageRegistrationMethodTest_14)
#set_tests_properties(itkImageRegistrationMethodTest_14 PROPERTIES #ATTACHED_FILES_ON_FAIL ${TEMP}/itkImageRegistrationMethodTest_14.txt)
itk_add_test(
  NAME itkImageRegistrationMethodTest_14
  COMMAND
    ITKRegistrationCommonTestDriver
    --full-output
    itkImageRegistrationMethodTest_14
)

itk_add_test(
  NAME itkImageRegistrationMethodTest_16
  COMMAND
    ITKRegistrationCommonTestDriver
    --redirectOutput
    ${TEMP}/itkImageRegistrationMethodTest_16.txt
    itkImageRegistrationMethodTest_16
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${TEMP}/itkImageRegistrationMethodTest_16.txt
)
set_tests_properties(
  itkImageRegistrationMethodTest_16
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${TEMP}/itkImageRegistrationMethodTest_16.txt
)

itk_add_test(
  NAME itkMeanSquaresPointSetToImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMeanSquaresPointSetToImageMetricTest
)
itk_add_test(
  NAME itkMutualInformationHistogramImageToImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMutualInformationHistogramImageToImageMetricTest
)
itk_add_test(
  NAME itkMeanReciprocalSquareDifferencePointSetToImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMeanReciprocalSquareDifferencePointSetToImageMetricTest
)
itk_add_test(
  NAME itkMultiResolutionImageRegistrationMethodTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMultiResolutionImageRegistrationMethodTest
)
itk_add_test(
  NAME itkMeanSquaresHistogramImageToImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMeanSquaresHistogramImageToImageMetricTest
)
itk_add_test(
  NAME itkNormalizedCorrelationPointSetToImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkNormalizedCorrelationPointSetToImageMetricTest
)
itk_add_test(
  NAME itkKullbackLeiblerCompareHistogramImageToImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkKullbackLeiblerCompareHistogramImageToImageMetricTest
)
itk_add_test(
  NAME itkNormalizedMutualInformationHistogramImageToImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkNormalizedMutualInformationHistogramImageToImageMetricTest
)
itk_add_test(
  NAME itkPointSetToSpatialObjectDemonsRegistrationTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkPointSetToSpatialObjectDemonsRegistrationTest
)
itk_add_test(
  NAME itkPointSetToImageRegistrationTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkPointSetToImageRegistrationTest
)
itk_add_test(
  NAME itkPointsLocatorTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkPointsLocatorTest
)
itk_add_test(
  NAME itkKappaStatisticImageToImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkKappaStatisticImageToImageMetricTest
    DATA{${ITK_DATA_ROOT}/Input/Spots.png}
)
itk_add_test(
  NAME itkMattesMutualInformationImageToImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMattesMutualInformationImageToImageMetricTest
    1
    1
)
itk_add_test(
  NAME itkMattesMutualInformationImageToImageMetricTest2
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMattesMutualInformationImageToImageMetricTest
    1
    0
)
itk_add_test(
  NAME itkMattesMutualInformationImageToImageMetricTest3
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMattesMutualInformationImageToImageMetricTest
    0
    1
)
itk_add_test(
  NAME itkMattesMutualInformationImageToImageMetricTest4
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMattesMutualInformationImageToImageMetricTest
    0
    0
)
itk_add_test(
  NAME itkMatchCardinalityImageToImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMatchCardinalityImageToImageMetricTest
    DATA{${ITK_DATA_ROOT}/Input/Spots.png}
)
itk_add_test(
  NAME itkMultiResolutionPyramidImageFilterWithResampleFilterTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMultiResolutionPyramidImageFilterTest
    Resample
)
itk_add_test(
  NAME itkMultiResolutionPyramidImageFilterWithShrinkFilterTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMultiResolutionPyramidImageFilterTest
    Shrink
)
itk_add_test(
  NAME itkRecursiveMultiResolutionPyramidImageFilterWithResampleFilterTest2
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMultiResolutionPyramidImageFilterTest
    Resample
    TestRecursive
)
itk_add_test(
  NAME itkRecursiveMultiResolutionPyramidImageFilterWithShrinkFilterTest2
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMultiResolutionPyramidImageFilterTest
    Shrink
    TestRecursive
)
itk_add_test(
  NAME itkImageRegistrationMethodTest_4
  COMMAND
    ITKRegistrationCommonTestDriver
    itkImageRegistrationMethodTest_4
)
itk_add_test(
  NAME itkImageRegistrationMethodTest_5
  COMMAND
    ITKRegistrationCommonTestDriver
    itkImageRegistrationMethodTest_5
)
itk_add_test(
  NAME itkImageRegistrationMethodTest_6
  COMMAND
    ITKRegistrationCommonTestDriver
    itkImageRegistrationMethodTest_6
)
itk_add_test(
  NAME itkImageRegistrationMethodTest_7
  COMMAND
    ITKRegistrationCommonTestDriver
    itkImageRegistrationMethodTest_7
)
itk_add_test(
  NAME itkImageRegistrationMethodTest_8
  COMMAND
    ITKRegistrationCommonTestDriver
    itkImageRegistrationMethodTest_8
)
itk_add_test(
  NAME itkImageRegistrationMethodTest_9
  COMMAND
    ITKRegistrationCommonTestDriver
    itkImageRegistrationMethodTest_9
)
itk_add_test(
  NAME itkRecursiveMultiResolutionPyramidImageFilterWithResampleFilterTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkRecursiveMultiResolutionPyramidImageFilterTest
    Resample
)
itk_add_test(
  NAME itkRecursiveMultiResolutionPyramidImageFilterWithShrinkFilterTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkRecursiveMultiResolutionPyramidImageFilterTest
    Shrink
)
itk_add_test(
  NAME itkNormalizedCorrelationImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkNormalizedCorrelationImageMetricTest
)
itk_add_test(
  NAME itkMeanReciprocalSquareDifferenceImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMeanReciprocalSquareDifferenceImageMetricTest
)
itk_add_test(
  NAME itkMeanSquaresImageMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMeanSquaresImageMetricTest
)
itk_add_test(
  NAME itkMutualInformationMetricTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkMutualInformationMetricTest
)
itk_add_test(
  NAME itkPointSetToPointSetRegistrationTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkPointSetToPointSetRegistrationTest
)
itk_add_test(
  NAME itkImageToSpatialObjectRegistrationTest
  COMMAND
    ITKRegistrationCommonTestDriver
    --redirectOutput
    itkImageToSpatialObjectRegistrationTest.txt
    itkImageToSpatialObjectRegistrationTest
)
set_tests_properties(
  itkImageToSpatialObjectRegistrationTest
  PROPERTIES
    ATTACHED_FILES_ON_FAIL
      ${ITK_TEST_OUTPUT_DIR}/itkImageToSpatialObjectRegistrationTest.txt
)
itk_add_test(
  NAME itkLandmarkBasedTransformInitializerTest
  COMMAND
    ITKRegistrationCommonTestDriver
    itkLandmarkBasedTransformInitializerTest
)
itk_add_test(
  NAME itkBlockMatchingImageFilterTest
  COMMAND
    ITKRegistrationCommonTestDriver
    --compare
    DATA{Baseline/itkBlockMatchingImageFilterTest.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkBlockMatchingImageFilterTest.mha
    itkBlockMatchingImageFilterTest
    DATA{${ITK_DATA_ROOT}/Input/HeadMRVolume.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkBlockMatchingImageFilterTest.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkBlockMatchingImageFilterTest.mha
)

itk_add_test(
  NAME itkEuclideanDistancePointMetricTestSquaredDistanceOff
  COMMAND
    ITKRegistrationCommonTestDriver
    itkEuclideanDistancePointMetricTest
    0
)
itk_add_test(
  NAME itkEuclideanDistancePointMetricTestSquaredDistanceOn
  COMMAND
    ITKRegistrationCommonTestDriver
    itkEuclideanDistancePointMetricTest
    1
)

set(
  ITKRegistrationGTests
  itkBSplineExponentialDiffeomorphicTransformParametersAdaptorGTest.cxx
  itkBSplineSmoothingOnUpdateDisplacementFieldTransformParametersAdaptorGTest.cxx
  itkBSplineTransformParametersAdaptorGTest.cxx
  itkCenteredTransformInitializerGTest.cxx
  itkCenteredVersorTransformInitializerGTest.cxx
  itkCompareHistogramImageToImageMetricGTest.cxx
  itkCorrelationCoefficientHistogramImageToImageMetricGTest.cxx
  itkDisplacementFieldTransformParametersAdaptorGTest.cxx
  itkGaussianExponentialDiffeomorphicTransformParametersAdaptorGTest.cxx
  itkGaussianSmoothingOnUpdateDisplacementFieldTransformParametersAdaptorGTest.cxx
  itkGradientDifferenceImageToImageMetricGTest.cxx
  itkHistogramImageToImageMetricGTest.cxx
  itkImageRegistrationMethodGTest.cxx
  itkImageRegistrationMethodGTest_1.cxx
  itkImageRegistrationMethodGTest_10.cxx
  itkImageRegistrationMethodGTest_11.cxx
  itkImageRegistrationMethodGTest_12.cxx
  itkImageRegistrationMethodGTest_13.cxx
  itkImageRegistrationMethodGTest_15.cxx
  itkImageRegistrationMethodGTest_17.cxx
  itkImageRegistrationMethodGTest_2.cxx
  itkImageRegistrationMethodGTest_3.cxx
  itkTransformInitializersGTest.cxx
)
creategoogletestdriver(ITKRegistration "${ITKRegistrationCommon-Test_LIBRARIES}" "${ITKRegistrationGTests}")

if(BUILD_EXAMPLES)
  #The historical examples from RegistrationITKv3 should no longer be used
  #as exemplars for best practices, but do provide reasonable historically
  #relevant tests to exercise the toolkit in ways that older software
  #bases may continue to use for backwards compatibility reasons.
  add_subdirectory(RegistrationITKv3)
endif()
