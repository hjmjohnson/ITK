itk_module_test()
set(
  ITKImageFunctionTests
  itkBSplineDecompositionImageFilterTest.cxx
  itkCentralDifferenceImageFunctionOnVectorSpeedTest.cxx
  itkCentralDifferenceImageFunctionSpeedTest.cxx
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
  NAME itkRayCastInterpolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkRayCastInterpolateImageFunctionTest
)
itk_add_test(
  NAME itkVectorMeanImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkVectorMeanImageFunctionTest
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
  itkImageAdaptorInterpolateImageFunctionGTest.cxx
  itkInterpolateGTest.cxx
  itkLabelImageGaussianInterpolateImageFunctionGTest.cxx
  itkLinearInterpolateImageFunctionGTest.cxx
  itkMahalanobisDistanceThresholdImageFunctionGTest.cxx
  itkMeanImageFunctionGTest.cxx
  itkMedianImageFunctionGTest.cxx
  itkNearestNeighborExtrapolateImageFunctionGTest.cxx
  itkSumOfSquaresImageFunctionGTest.cxx
  itkVarianceImageFunctionGTest.cxx
)
creategoogletestdriver(ITKImageFunction "${ITKImageFunction-Test_LIBRARIES}" "${ITKImageFunctionGTests}")
