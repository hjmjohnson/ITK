itk_module_test()
set(
  ITKImageFunctionTests
  itkBSplineDecompositionImageFilterTest.cxx
  itkCentralDifferenceImageFunctionOnVectorSpeedTest.cxx
  itkCentralDifferenceImageFunctionSpeedTest.cxx
  itkVectorLinearInterpolateNearestNeighborExtrapolateImageFunctionTest.cxx
  itkVectorMeanImageFunctionTest.cxx
  itkWindowedSincInterpolateImageFunctionTest.cxx
)

createtestdriver(ITKImageFunction "${ITKImageFunction-Test_LIBRARIES}" "${ITKImageFunctionTests}")

itk_add_test(
  NAME itkBSplineDecompositionImageFilterTest
  COMMAND
    ITKImageFunctionTestDriver
    itkBSplineDecompositionImageFilterTest
    3
    -0.26794919243112281
)
itk_add_test(
  NAME itkVectorMeanImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkVectorMeanImageFunctionTest
)

itk_add_test(
  NAME itkWindowedSincInterpolateImageFunctionTest
  COMMAND
    ITKImageFunctionTestDriver
    itkWindowedSincInterpolateImageFunctionTest
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
  itkNearestNeighborInterpolateImageFunctionGTest.cxx
  itkNeighborhoodOperatorImageFunctionGTest.cxx
  itkRayCastInterpolateImageFunctionGTest.cxx
  itkRGBInterpolateImageFunctionGTest.cxx
  itkScatterMatrixImageFunctionGTest.cxx
  itkSumOfSquaresImageFunctionGTest.cxx
  itkVarianceImageFunctionGTest.cxx
  itkVectorInterpolateImageFunctionGTest.cxx
)
creategoogletestdriver(ITKImageFunction "${ITKImageFunction-Test_LIBRARIES}" "${ITKImageFunctionGTests}")
