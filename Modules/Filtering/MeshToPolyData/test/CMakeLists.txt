itk_module_test()

set(
  MeshToPolyDataTests
  itkImageToPointSetFilterTest.cxx
  itkMeshToPolyDataFilterTest.cxx
  itkPolyDataToMeshFilterTest.cxx
)

createtestdriver(MeshToPolyData "${MeshToPolyData-Test_LIBRARIES}" "${MeshToPolyDataTests}")

itk_add_test(
  NAME itkMeshToPolyDataFilterTest
  COMMAND
    MeshToPolyDataTestDriver
    itkMeshToPolyDataFilterTest
    DATA{Input/cow.vtk}
    ${ITK_TEST_OUTPUT_DIR}/itkMeshToPolyDataFilterTest.vtk
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkMeshToPolyDataFilterTest.vtk
)

itk_add_test(
  NAME itkImageToPointSetFilterTest
  COMMAND
    MeshToPolyDataTestDriver
    itkImageToPointSetFilterTest
    DATA{Input/foot.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkImageToPointSetFilterTestOutput.vtk
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkImageToPointSetFilterTestOutput.vtk
)

itk_add_test(
  NAME itkPolyDataToMeshFilterTest
  COMMAND
    MeshToPolyDataTestDriver
    itkPolyDataToMeshFilterTest
)

set(
  MeshToPolyDataGTests
  itkMeshToPolyDataFilterCellDataGTest.cxx
  itkMeshToPolyDataFilterLinePolyLineCellDataGTest.cxx
  itkPolyDataGTest.cxx
)
creategoogletestdriver(MeshToPolyData "${MeshToPolyData-Test_LIBRARIES}" "${MeshToPolyDataGTests}")
