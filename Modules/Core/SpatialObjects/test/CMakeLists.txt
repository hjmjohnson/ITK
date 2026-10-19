itk_module_test()
set(
  ITKSpatialObjectsTests
  itkBoxSpatialObjectTest.cxx
  itkImageMaskSpatialObjectTest.cxx
  itkImageMaskSpatialObjectTest5.cxx
  itkImageSpatialObjectTest.cxx
  itkLandmarkSpatialObjectTest.cxx
  itkLineSpatialObjectTest.cxx
  itkMeshSpatialObjectTest.cxx
  itkMetaArrowConverterTest.cxx
  itkMetaGaussianConverterTest.cxx
  itkNewMetaObjectTypeTest.cxx
  itkPolygonSpatialObjectIsInsideInObjectSpaceTest.cxx
  itkPolygonSpatialObjectTest.cxx
  itkSpatialObjectDuplicatorTest.cxx
  itkSpatialObjectToImageFilterTest.cxx
  itkSpatialObjectToImageStatisticsCalculatorTest.cxx
  itkSpatialObjectToPointSetFilterTest.cxx
  itkSurfaceSpatialObjectTest.cxx
  itkTubeSpatialObjectTest.cxx
)

createtestdriver(ITKSpatialObjects "${ITKSpatialObjects-Test_LIBRARIES}" "${ITKSpatialObjectsTests}")

itk_add_test(
  NAME itkSpatialObjectToImageFilterTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkSpatialObjectToImageFilterTest
)
itk_add_test(
  NAME itkLandmarkSpatialObjectTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkLandmarkSpatialObjectTest
)
itk_add_test(
  NAME itkImageSpatialObjectTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkImageSpatialObjectTest
)
itk_add_test(
  NAME itkSpatialObjectToImageStatisticsCalculatorTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkSpatialObjectToImageStatisticsCalculatorTest
)
itk_add_test(
  NAME itkImageMaskSpatialObjectTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkImageMaskSpatialObjectTest
)
itk_add_test(
  NAME itkImageMaskSpatialObjectTest5
  COMMAND
    ITKSpatialObjectsTestDriver
    itkImageMaskSpatialObjectTest5
)
itk_add_test(
  NAME itkSurfaceSpatialObjectTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkSurfaceSpatialObjectTest
)
itk_add_test(
  NAME itkMetaArrowConverterTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkMetaArrowConverterTest
    ${ITK_TEST_OUTPUT_DIR}/MetaArrowConverterTestFile.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/MetaArrowConverterTestFile.mha
)
itk_add_test(
  NAME itkMetaGaussianConverterTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkMetaGaussianConverterTest
    ${ITK_TEST_OUTPUT_DIR}/MetaGaussianConverterTest.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/MetaGaussianConverterTest.mha
)
itk_add_test(
  NAME itkTubeSpatialObjectTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkTubeSpatialObjectTest
)
itk_add_test(
  NAME itkSpatialObjectToPointSetFilterTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkSpatialObjectToPointSetFilterTest
)
itk_add_test(
  NAME itkSpatialObjectDuplicatorTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkSpatialObjectDuplicatorTest
)
itk_add_test(
  NAME itkBoxSpatialObjectTest
  COMMAND
    ITKSpatialObjectsTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/SpatialObjects/BoxSpatialObjectTest.png}
    ${ITK_TEST_OUTPUT_DIR}/BoxSpatialObjectTest.png
    itkBoxSpatialObjectTest
    ${ITK_TEST_OUTPUT_DIR}/BoxSpatialObjectTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/BoxSpatialObjectTest.png
)
itk_add_test(
  NAME itkPolygonSpatialObjectTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkPolygonSpatialObjectTest
)
itk_add_test(
  NAME itkPolygonSpatialObjectIsInsideInObjectSpaceTest
  COMMAND
    ITKSpatialObjectsTestDriver
    --compareIntensityTolerance
    0
    --compare
    DATA{Baseline/itkPolygonSpatialObjectIsInsideInObjectSpaceTest.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkPolygonSpatialObjectIsInsideInObjectSpaceTest.mha
    itkPolygonSpatialObjectIsInsideInObjectSpaceTest
    DATA{Input/PolygonContourPoints.csv}
    DATA{Baseline/itkPolygonSpatialObjectIsInsideInObjectSpaceTest.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkPolygonSpatialObjectIsInsideInObjectSpaceTest.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkPolygonSpatialObjectIsInsideInObjectSpaceTest.mha
)
itk_add_test(
  NAME itkMeshSpatialObjectTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkMeshSpatialObjectTest
)
itk_add_test(
  NAME itkLineSpatialObjectTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkLineSpatialObjectTest
)
itk_add_test(
  NAME itkNewMetaObjectTypeTest
  COMMAND
    ITKSpatialObjectsTestDriver
    itkNewMetaObjectTypeTest
    ${ITK_TEST_OUTPUT_DIR}/NewMetaObjectType.meta
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/NewMetaObjectType.meta
)

set(
  ITKSpatialObjectsGTests
  itkImageMaskSpatialObjectGTest.cxx
  itkArrowSpatialObjectGTest.cxx
  itkBlobSpatialObjectGTest.cxx
  itkCastSpatialObjectFilterGTest.cxx
  itkContourSpatialObjectGTest.cxx
  itkContourSpatialObjectPointGTest.cxx
  itkDTITubeSpatialObjectGTest.cxx
  itkEllipseSpatialObjectGTest.cxx
  itkGaussianSpatialObjectGTest.cxx
  itkImageMaskSpatialObjectGTest2.cxx
  itkImageMaskSpatialObjectGTest3.cxx
  itkImageMaskSpatialObjectGTest4.cxx
  itkSpatialObjectPointGTest.cxx
)
creategoogletestdriver(ITKSpatialObjects "${ITKSpatialObjects-Test_LIBRARIES}" "${ITKSpatialObjectsGTests}")
