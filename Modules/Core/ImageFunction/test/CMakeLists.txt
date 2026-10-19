itk_module_test()
set(
  ITKImageFunctionTests
  itkBSplineDecompositionImageFilterTest.cxx
  itkCentralDifferenceImageFunctionOnVectorSpeedTest.cxx
  itkCentralDifferenceImageFunctionSpeedTest.cxx
  itkImageAdaptorInterpolateImageFunctionTest.cxx
  itkInterpolateTest.cxx
  itkLabelImageGaussianInterpolateImageFunctionTest.cxx
  itkLinearInterpolateImageFunctionTest.cxx
  itkMahalanobisDistanceThresholdImageFunctionTest.cxx
  itkMeanImageFunctionTest.cxx
  itkMedianImageFunctionTest.cxx
  itkNearestNeighborExtrapolateImageFunctionTest.cxx
  itkNearestNeighborInterpolateImageFunctionTest.cxx
  itkNeighborhoodOperatorImageFunctionTest.cxx
  itkRayCastInterpolateImageFunctionTest.cxx
  itkRGBInterpolateImageFunctionTest.cxx
  itkScatterMatrixImageFunctionTest.cxx
  itkVectorInterpolateImageFunctionTest.cxx
  itkVectorLinearInterpolateNearestNeighborExtrapolateImageFunctionTest.cxx
  itkVectorMeanImageFunctionTest.cxx
  itkWindowedSincInterpolateImageFunctionTest.cxx
)

createtestdriver(ITKImageFunction "${ITKImageFunction-Test_LIBRARIES}" "${ITKImageFunctionTests}")

itk_add_test(
  NAME itkVectorInterpolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkVectorInterpolateImageFunctionTest
)
itk_add_test(
  NAME itkMedianImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkMedianImageFunctionTest
)
itk_add_test(
  NAME itkBSplineDecompositionImageFilterTest
  COMMAND
    ITKImageFunctionTestDriver
    itkBSplineDecompositionImageFilterTest
    3
    -0.26794919243112281
)
itk_add_test(
  NAME itkScatterMatrixImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkScatterMatrixImageFunctionTest
)
itk_add_test(
  NAME itkMeanImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkMeanImageFunctionTest
)
itk_add_test(
  NAME itkImageAdaptorInterpolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkImageAdaptorInterpolateImageFunctionTest
)
itk_add_test(
  NAME itkRayCastInterpolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkRayCastInterpolateImageFunctionTest
)
itk_add_test(
  NAME itkNearestNeighborExtrapolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkNearestNeighborExtrapolateImageFunctionTest
)
itk_add_test(
  NAME itkVectorMeanImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkVectorMeanImageFunctionTest
)
itk_add_test(
  NAME itkMahalanobisDistanceThresholdImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkMahalanobisDistanceThresholdImageFunctionTest
)
itk_add_test(
  NAME itkInterpolateTest
  COMMAND
    ITKImageFunctionTestDriver
    itkInterpolateTest
)
itk_add_test(
  NAME itkRGBInterpolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkRGBInterpolateImageFunctionTest
)

itk_add_test(
  NAME itkWindowedSincInterpolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkWindowedSincInterpolateImageFunctionTest
)
itk_add_test(
  NAME itkLinearInterpolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkLinearInterpolateImageFunctionTest
)
itk_add_test(
  NAME itkNeighborhoodOperatorImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkNeighborhoodOperatorImageFunctionTest
)
itk_add_test(
  NAME itkNearestNeighborInterpolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkNearestNeighborInterpolateImageFunctionTest
)
itk_add_test(
  NAME itkLabelImageGaussianInterpolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkLabelImageGaussianInterpolateImageFunctionTest
)

itk_add_test(
  NAME itkVectorLinearInterpolateNearestNeighborExtrapolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkVectorLinearInterpolateNearestNeighborExtrapolateImageFunctionTest
)

set(
  ITKImageFunctionGTests
  itkBinaryThresholdImageFunctionGTest.cxx
  itkBSplineInterpolateImageFunctionGTest.cxx
  itkBSplineResampleImageFunctionGTest.cxx
  itkCentralDifferenceImageFunctionGTest.cxx
  itkCentralDifferenceImageFunctionOnVectorGTest.cxx
  itkCovarianceImageFunctionGTest.cxx
  itkGaussianBlurImageFunctionGTest.cxx
  itkGaussianDerivativeImageFunctionGTest.cxx
  itkGaussianInterpolateImageFunctionGTest.cxx
  itkSumOfSquaresImageFunctionGTest.cxx
  itkVarianceImageFunctionGTest.cxx
)
creategoogletestdriver(ITKImageFunction "${ITKImageFunction-Test_LIBRARIES}" "${ITKImageFunctionGTests}")
