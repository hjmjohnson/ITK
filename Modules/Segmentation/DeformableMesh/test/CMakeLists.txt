itk_module_test()
set(
  ITKDeformableMeshTests
  itkDeformableSimplexMesh3DBalloonForceFilterTest.cxx
  itkDeformableSimplexMesh3DGradientConstraintForceFilterTest.cxx
)

createtestdriver(ITKDeformableMesh "${ITKDeformableMesh-Test_LIBRARIES}" "${ITKDeformableMeshTests}")

set(
  ITKDeformableMeshGTests
  itkDeformableSimplexMesh3DFilterGTest.cxx
  itkSimplexMeshWithFloatCoordRepGTest.cxx
)
creategoogletestdriver(ITKDeformableMesh "${ITKDeformableMesh-Test_LIBRARIES}" "${ITKDeformableMeshGTests}")

itk_add_test(
  NAME itkDeformableSimplexMesh3DBalloonForceFilterTest
  COMMAND
    ITKDeformableMeshTestDriver
    itkDeformableSimplexMesh3DBalloonForceFilterTest
    0.01
)
itk_add_test(
  NAME itkDeformableSimplexMesh3DGradientConstaintForceFilterTest
  COMMAND
    ITKDeformableMeshTestDriver
    itkDeformableSimplexMesh3DGradientConstraintForceFilterTest
)
