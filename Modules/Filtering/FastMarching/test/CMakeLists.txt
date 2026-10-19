itk_module_test()

set(
  ITKFastMarchingTests
  itkFastMarchingTest.cxx
  itkFastMarchingTest2.cxx
  itkFastMarchingUpwindGradientTest.cxx
  # New files
  itkFastMarchingBaseTest.cxx
  itkFastMarchingImageFilterBaseTest.cxx
  itkFastMarchingImageTopologicalTest.cxx
  itkFastMarchingQuadEdgeMeshFilterWithNumberOfElementsTest.cxx
  itkFastMarchingStoppingCriterionBaseTest.cxx
  itkFastMarchingThresholdStoppingCriterionTest.cxx
  itkFastMarchingUpwindGradientBaseTest.cxx
)

createtestdriver(ITKFastMarching "${ITKFastMarching-Test_LIBRARIES}" "${ITKFastMarchingTests}")

itk_add_test(
  NAME itkFastMarchingTest
  COMMAND
    ITKFastMarchingTestDriver
    itkFastMarchingTest
    1.0
    1.0
    100.0
    0
    0
    1.0
    0.0
    0
)
itk_add_test(
  NAME itkFastMarchingTest2
  COMMAND
    ITKFastMarchingTestDriver
    itkFastMarchingTest2
)
itk_add_test(
  NAME itkFastMarchingUpwindGradientTest
  COMMAND
    ITKFastMarchingTestDriver
    itkFastMarchingUpwindGradientTest
)

itk_add_test(
  NAME itkFastMarchingBaseTest0
  COMMAND
    ITKFastMarchingTestDriver
    itkFastMarchingBaseTest
    0
)
itk_add_test(
  NAME itkFastMarchingBaseTest1
  COMMAND
    ITKFastMarchingTestDriver
    itkFastMarchingBaseTest
    1
)

itk_add_test(
  NAME itkFastMarchingImageFilterBaseTest
  COMMAND
    ITKFastMarchingTestDriver
    itkFastMarchingImageFilterBaseTest
)

itk_add_test(
  NAME itkFastMarchingUpwindGradientBaseTest
  COMMAND
    ITKFastMarchingTestDriver
    itkFastMarchingUpwindGradientBaseTest
)

itk_add_test(
  NAME itkFastMarchingQuadEdgeMeshFilterWithNumberOfElementsTest
  COMMAND
    ITKFastMarchingTestDriver
    itkFastMarchingQuadEdgeMeshFilterWithNumberOfElementsTest
)

itk_add_test(
  NAME itkFastMarchingStoppingCriterionBaseTest
  COMMAND
    ITKFastMarchingTestDriver
    itkFastMarchingStoppingCriterionBaseTest
)

itk_add_test(
  NAME itkFastMarchingThresholdStoppingCriterionTest
  COMMAND
    ITKFastMarchingTestDriver
    itkFastMarchingThresholdStoppingCriterionTest
)

# -------------------------------------------------------------------------
# Topology constrained front propagation
# -------------------------------------------------------------------------

# ************************************************************************
# 2D

itk_add_test(
  NAME itkFastMarchingImageFilterTest_Brain2D_SingleSeed_NoTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_singleSeed_NoTopo.nii.gz
    DATA{Baseline/BrainProtonDensitySlice_singleSeed_NoTopo_out.nii.gz}
    itkFastMarchingImageTopologicalTest
    2
    DATA{Baseline/BrainProtonDensitySlice_speed.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_singleSeed_NoTopo.nii.gz
    DATA{Baseline/BrainProtonDensitySlice_singleSeed.nii.gz}
    150
    0
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_singleSeed_NoTopo.nii.gz
)

itk_add_test(
  NAME itkFastMarchingImageFilterTest_Brain2D_SingleSeed_StrictTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    DATA{Baseline/BrainProtonDensitySlice_singleSeed_StrictTopo_out.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_singleSeed_StrictTopo.nii.gz
    itkFastMarchingImageTopologicalTest
    2
    DATA{Baseline/BrainProtonDensitySlice_speed.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_singleSeed_StrictTopo.nii.gz
    DATA{Baseline/BrainProtonDensitySlice_singleSeed.nii.gz}
    150
    1
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_singleSeed_StrictTopo.nii.gz
)

itk_add_test(
  NAME itkFastMarchingImageFilterTest_Brain2D_SingleSeed_NoHandlesTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_singleSeed_NoHandlesTopo.nii.gz
    DATA{Baseline/BrainProtonDensitySlice_singleSeed_NoHandlesTopo_out.nii.gz}
    itkFastMarchingImageTopologicalTest
    2
    DATA{Baseline/BrainProtonDensitySlice_speed.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_singleSeed_NoHandlesTopo.nii.gz
    DATA{Baseline/BrainProtonDensitySlice_singleSeed.nii.gz}
    150
    2
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_singleSeed_NoHandlesTopo.nii.gz
)

itk_add_test(
  NAME itkFastMarchingImageFilterTest_Brain2D_multipleSeeds_NoTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    DATA{Baseline/BrainProtonDensitySlice_multipleSeeds_NoTopo_out.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_multipleSeeds_NoTopo.nii.gz
    itkFastMarchingImageTopologicalTest
    2
    DATA{Baseline/BrainProtonDensitySlice_speed.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_multipleSeeds_NoTopo.nii.gz
    DATA{Baseline/BrainProtonDensitySlice_multipleSeeds.nii.gz}
    150
    0
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_multipleSeeds_NoTopo.nii.gz
)

itk_add_test(
  NAME itkFastMarchingImageFilterTest_Brain2D_multipleSeeds_StrictTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    DATA{Baseline/BrainProtonDensitySlice_multipleSeeds_StrictTopo_out.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_multipleSeeds_StrictTopo.nii.gz
    itkFastMarchingImageTopologicalTest
    2
    DATA{Baseline/BrainProtonDensitySlice_speed.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_multipleSeeds_StrictTopo.nii.gz
    DATA{Baseline/BrainProtonDensitySlice_multipleSeeds.nii.gz}
    150
    1
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_multipleSeeds_StrictTopo.nii.gz
)

itk_add_test(
  NAME itkFastMarchingImageFilterTest_Brain2D_multipleSeeds_NoHandlesTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    DATA{Baseline/BrainProtonDensitySlice_multipleSeeds_NoHandlesTopo_out.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_multipleSeeds_NoHandlesTopo.nii.gz
    itkFastMarchingImageTopologicalTest
    2
    DATA{Baseline/BrainProtonDensitySlice_speed.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_multipleSeeds_NoHandlesTopo.nii.gz
    DATA{Baseline/BrainProtonDensitySlice_multipleSeeds.nii.gz}
    150
    2
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_Brain2D_multipleSeeds_NoHandlesTopo.nii.gz
)

# ************************************************************************
# 3D
itk_add_test(
  NAME itkFastMarchingImageFilterTest_torus_multipleSeeds_NoTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    DATA{Baseline/torus_multipleSeeds_NoTopo_out.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_torus_multipleSeeds_NoTopo.nii.gz
    itkFastMarchingImageTopologicalTest
    3
    DATA{Baseline/torus.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_torus_multipleSeeds_NoTopo.nii.gz
    DATA{Baseline/torus_multipleSeeds.nii.gz}
    150
    0
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_torus_multipleSeeds_NoTopo.nii.gz
)

itk_add_test(
  NAME itkFastMarchingImageFilterTest_torus_multipleSeeds_StrictTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    DATA{Baseline/torus_multipleSeeds_StrictTopo_out.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_torus_multipleSeeds_StrictTopo.nii.gz
    itkFastMarchingImageTopologicalTest
    3
    DATA{Baseline/torus.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_torus_multipleSeeds_StrictTopo.nii.gz
    DATA{Baseline/torus_multipleSeeds.nii.gz}
    150
    1
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_torus_multipleSeeds_StrictTopo.nii.gz
)

itk_add_test(
  NAME itkFastMarchingImageFilterTest_torus_multipleSeeds_NoHandlesTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    DATA{Baseline/torus_multipleSeeds_NoHandlesTopo_out.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_torus_multipleSeeds_NoHandlesTopo.nii.gz
    itkFastMarchingImageTopologicalTest
    3
    DATA{Baseline/torus.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_torus_multipleSeeds_NoHandlesTopo.nii.gz
    DATA{Baseline/torus_multipleSeeds.nii.gz}
    150
    2
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_torus_multipleSeeds_NoHandlesTopo.nii.gz
)

itk_add_test(
  NAME itkFastMarchingImageFilterTest_wm_multipleSeeds_NoTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    DATA{Baseline/wm_multipleSeeds_NoTopo_out.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_wm_multipleSeeds_NoTopo.nii.gz
    itkFastMarchingImageTopologicalTest
    3
    DATA{Baseline/wm.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_wm_multipleSeeds_NoTopo.nii.gz
    DATA{Baseline/wm_multipleSeeds.nii.gz}
    150
    0
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_wm_multipleSeeds_NoTopo.nii.gz
)
set_property(
  TEST
    itkFastMarchingImageFilterTest_wm_multipleSeeds_NoTopo
  APPEND
  PROPERTY
    LABELS
      RUNS_LONG
)

itk_add_test(
  NAME itkFastMarchingImageFilterTest_wm_multipleSeeds_StrictTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    DATA{Baseline/wm_multipleSeeds_StrictTopo_out.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_wm_multipleSeeds_StrictTopo.nii.gz
    itkFastMarchingImageTopologicalTest
    3
    DATA{Baseline/wm.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_wm_multipleSeeds_StrictTopo.nii.gz
    DATA{Baseline/wm_multipleSeeds.nii.gz}
    150
    1
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_wm_multipleSeeds_StrictTopo.nii.gz
)
set_property(
  TEST
    itkFastMarchingImageFilterTest_wm_multipleSeeds_StrictTopo
  APPEND
  PROPERTY
    LABELS
      RUNS_LONG
)

itk_add_test(
  NAME itkFastMarchingImageFilterTest_wm_multipleSeeds_NoHandlesTopo
  COMMAND
    ITKFastMarchingTestDriver
    --compare
    DATA{Baseline/wm_multipleSeeds_NoHandlesTopo_out.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_wm_multipleSeeds_NoHandlesTopo.nii.gz
    itkFastMarchingImageTopologicalTest
    3
    DATA{Baseline/wm.nii.gz}
    ${ITK_TEST_OUTPUT_DIR}/test_wm_multipleSeeds_NoHandlesTopo.nii.gz
    DATA{Baseline/wm_multipleSeeds.nii.gz}
    150
    2
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/test_wm_multipleSeeds_NoHandlesTopo.nii.gz
)
set_property(
  TEST
    itkFastMarchingImageFilterTest_wm_multipleSeeds_NoHandlesTopo
  APPEND
  PROPERTY
    LABELS
      RUNS_LONG
)

set(
  ITKFastMarchingGTests
  itkFastMarchingExtensionImageFilterGTest.cxx
  itkFastMarchingImageFilterBaseGTest.cxx
  itkFastMarchingImageFilterRealGTest1.cxx
  itkFastMarchingImageFilterRealGTest2.cxx
  itkFastMarchingImageFilterRealWithNumberOfElementsGTest.cxx
  itkFastMarchingNumberOfElementsStoppingCriterionGTest.cxx
  itkFastMarchingQuadEdgeMeshFilterBaseGTest.cxx
  itkFastMarchingQuadEdgeMeshFilterBaseGTest2.cxx
  itkFastMarchingQuadEdgeMeshFilterBaseGTest3.cxx
  itkFastMarchingQuadEdgeMeshFilterBaseGTest4.cxx
  itkFastMarchingUpwindGradientImageFilterGTest.cxx
)
creategoogletestdriver(ITKFastMarching "${ITKFastMarching-Test_LIBRARIES}" "${ITKFastMarchingGTests}")
