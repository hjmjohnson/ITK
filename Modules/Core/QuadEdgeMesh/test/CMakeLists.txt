itk_module_test()
set(
  ITKQuadEdgeMeshTests
  itkQuadEdgeMeshAddFaceTest1.cxx
  itkQuadEdgeMeshEulerOperatorJoinVertexTest.cxx
  itkQuadEdgeMeshScalarDataVTKPolyDataWriterTest1.cxx
  itkQuadEdgeMeshTest3.cxx
  itkQuadEdgeTest1.cxx
  itkVTKPolyDataIOQuadEdgeMeshTest.cxx
  itkVTKPolyDataReaderQuadEdgeMeshTest.cxx
)

createtestdriver(ITKQuadEdgeMesh "${ITKQuadEdgeMesh-Test_LIBRARIES}" "${ITKQuadEdgeMeshTests}")

itk_add_test(
  NAME itkQuadEdgeMeshTest3
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshTest3
)
itk_add_test(
  NAME itkQuadEdgeMeshScalarDataVTKPolyDataWriterTest1
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshScalarDataVTKPolyDataWriterTest1
    ${ITK_TEST_OUTPUT_DIR}/sphere.vtk
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/sphere.vtk
)
itk_add_test(
  NAME itkQuadEdgeTest1
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeTest1
)
itk_add_test(
  NAME itkQuadEdgeMeshAddFaceTest1_0
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshAddFaceTest1
    0
)
itk_add_test(
  NAME itkQuadEdgeMeshAddFaceTest1_1
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshAddFaceTest1
    1
)
itk_add_test(
  NAME itkQuadEdgeMeshAddFaceTest1_2
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshAddFaceTest1
    2
)
itk_add_test(
  NAME itkQuadEdgeMeshAddFaceTest1_3
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshAddFaceTest1
    3
)
itk_add_test(
  NAME itkQuadEdgeMeshAddFaceTest1_4
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshAddFaceTest1
    4
)
itk_add_test(
  NAME itkQuadEdgeMeshAddFaceTest1_5
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshAddFaceTest1
    5
)
itk_add_test(
  NAME itkQuadEdgeMeshEulerOperatorJoinVertexTest0
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshEulerOperatorJoinVertexTest
    0
)
itk_add_test(
  NAME itkQuadEdgeMeshEulerOperatorJoinVertexTest1
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshEulerOperatorJoinVertexTest
    1
)
itk_add_test(
  NAME itkQuadEdgeMeshEulerOperatorJoinVertexTest2
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshEulerOperatorJoinVertexTest
    2
)
itk_add_test(
  NAME itkQuadEdgeMeshEulerOperatorJoinVertexTest3
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshEulerOperatorJoinVertexTest
    3
)
itk_add_test(
  NAME itkQuadEdgeMeshEulerOperatorJoinVertexTest4
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkQuadEdgeMeshEulerOperatorJoinVertexTest
    4
)
itk_add_test(
  NAME itkVTKPolyDataIOQuadEdgeMeshTest
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkVTKPolyDataIOQuadEdgeMeshTest
    DATA{${ITK_DATA_ROOT}/Input/genusZeroSurface01.vtk}
    ${ITK_TEST_OUTPUT_DIR}/VTKPolyDataIOTest.vtk
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/VTKPolyDataIOTest.vtk
)
itk_add_test(
  NAME itkVTKPolyDataReaderQuadEdgeMeshTest
  COMMAND
    ITKQuadEdgeMeshTestDriver
    itkVTKPolyDataReaderQuadEdgeMeshTest
    DATA{${ITK_DATA_ROOT}/Input/genusZeroSurface01.vtk}
)

set(
  ITKQuadEdgeMeshGTests
  itkDynamicQuadEdgeMeshGTest.cxx
  itkGeometricalQuadEdgeGTest1.cxx
  itkQuadEdgeMeshAddFaceGTest2.cxx
  itkQuadEdgeMeshBasicLayerGTest.cxx
  itkQuadEdgeMeshCellInterfaceGTest.cxx
  itkQuadEdgeMeshCountingCellsGTest.cxx
  itkQuadEdgeMeshDeleteEdgeGTest.cxx
  itkQuadEdgeMeshDeletePointAndReorderIDsGTest.cxx
  itkQuadEdgeMeshEulerOperatorCreateCenterVertexGTest.cxx
  itkQuadEdgeMeshEulerOperatorDeleteCenterVertexGTest.cxx
  itkQuadEdgeMeshEulerOperatorFlipGTest.cxx
  itkQuadEdgeMeshEulerOperatorJoinFacetGTest.cxx
  itkQuadEdgeMeshEulerOperatorSplitEdgeGTest.cxx
  itkQuadEdgeMeshEulerOperatorSplitFaceGTest.cxx
  itkQuadEdgeMeshEulerOperatorSplitVertexGTest.cxx
  itkQuadEdgeMeshFrontIteratorGTest.cxx
  itkQuadEdgeMeshGTest1.cxx
  itkQuadEdgeMeshGTest2.cxx
  itkQuadEdgeMeshIteratorGTest.cxx
  itkQuadEdgeMeshNoPointConstGTest.cxx
  itkQuadEdgeMeshPointGTest1.cxx
  itkQuadEdgeMeshPolygonCellGTest.cxx
  itkQuadEdgeMeshTypeTraitsGTest.cxx
)
creategoogletestdriver(ITKQuadEdgeMesh "${ITKQuadEdgeMesh-Test_LIBRARIES}" "${ITKQuadEdgeMeshGTests}")
