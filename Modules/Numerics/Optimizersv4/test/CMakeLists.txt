itk_module_test()
set(
  ITKOptimizersv4Tests
  itkAutoScaledGradientDescentRegistrationOnVectorTest.cxx
  itkAutoScaledGradientDescentRegistrationTest.cxx
  itkLBFGSBOptimizerv4Test.cxx
  itkLBFGSOptimizerv4Test.cxx
  itkMultiGradientOptimizerv4Test.cxx
  itkMultiStartOptimizerv4Test.cxx
  itkObjectToObjectMetricBaseTest.cxx
  itkObjectToObjectOptimizerBaseTest.cxx
  itkOnePlusOneEvolutionaryOptimizerv4Test.cxx
  itkOptimizerParameterScalesEstimatorTest.cxx
  itkPowellOptimizerv4Test.cxx
  itkQuasiNewtonOptimizerv4Test.cxx
  itkRegistrationParameterScalesEstimatorTest.cxx
  itkRegistrationParameterScalesFromIndexShiftTest.cxx
  itkRegistrationParameterScalesFromJacobianTest.cxx
  itkRegistrationParameterScalesFromPhysicalShiftPointSetTest.cxx
  itkRegistrationParameterScalesFromPhysicalShiftTest.cxx
  itkRegularStepGradientDescentOptimizerv4Test.cxx
)

set(INPUTDATA ${ITK_DATA_ROOT}/Input)
set(BASELINE_ROOT ${ITK_DATA_ROOT}/Baseline)
set(TEMP ${ITK_TEST_OUTPUT_DIR})

createtestdriver(ITKOptimizersv4 "${ITKOptimizersv4-Test_LIBRARIES}" "${ITKOptimizersv4Tests}")

set(
  ITKOptimizersv4GTests
  itkAmoebaOptimizerv4GTest.cxx
  itkConjugateGradientLineSearchOptimizerv4GTest.cxx
  itkExhaustiveOptimizerv4GTest.cxx
  itkGradientDescentLineSearchOptimizerv4GTest.cxx
  itkGradientDescentOptimizerBasev4GTest.cxx
  itkGradientDescentOptimizerv4GTest.cxx
  itkGradientDescentOptimizerv4GTest2.cxx
  itkGradientDescentOptimizerv4ObserverGTest.cxx
  itkLBFGS2Optimizerv4GTest.cxx
  itkMultiGradientOptimizerv4GTest.cxx
  itkObjectToObjectMetricGTest.cxx
  itkWindowConvergenceMonitoringFunctionGTest.cxx
)
creategoogletestdriver(ITKOptimizersv4 "${ITKOptimizersv4-Test_LIBRARIES}" "${ITKOptimizersv4GTests}")

itk_add_test(
  NAME itkObjectToObjectOptimizerBaseTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkObjectToObjectOptimizerBaseTest
)

itk_add_test(
  NAME itkMultiStartOptimizerv4Test
  COMMAND
    ITKOptimizersv4TestDriver
    itkMultiStartOptimizerv4Test
)

itk_add_test(
  NAME itkMultiGradientOptimizerv4Test
  COMMAND
    ITKOptimizersv4TestDriver
    itkMultiGradientOptimizerv4Test
)

itk_add_test(
  NAME itkOptimizerParameterScalesEstimatorTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkOptimizerParameterScalesEstimatorTest
)

itk_add_test(
  NAME itkRegistrationParameterScalesEstimatorTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkRegistrationParameterScalesEstimatorTest
)

itk_add_test(
  NAME itkRegistrationParameterScalesFromPhysicalShiftTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkRegistrationParameterScalesFromPhysicalShiftTest
)

itk_add_test(
  NAME itkRegistrationParameterScalesFromJacobianTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkRegistrationParameterScalesFromJacobianTest
)

itk_add_test(
  NAME itkAutoScaledGradientDescentRegistrationTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkAutoScaledGradientDescentRegistrationTest
    30
    1.0
    1
    0
    1
)

itk_add_test(
  NAME itkAutoScaledGradientDescentRegistrationTest2
  COMMAND
    ITKOptimizersv4TestDriver
    itkAutoScaledGradientDescentRegistrationTest
    30
    1.0
    0
    1
    1
)

itk_add_test(
  NAME itkAutoScaledGradientDescentRegistrationTest3
  COMMAND
    ITKOptimizersv4TestDriver
    itkAutoScaledGradientDescentRegistrationTest
    30
    1.0
    0
    0
    1
)

itk_add_test(
  NAME itkAutoScaledGradientDescentRegistrationTest4
  COMMAND
    ITKOptimizersv4TestDriver
    itkAutoScaledGradientDescentRegistrationTest
    30
    1.0
    0
    1
    0
)

itk_add_test(
  NAME itkAutoScaledGradientDescentRegistrationOnVectorTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkAutoScaledGradientDescentRegistrationOnVectorTest
    30
    1.0
)

itk_add_test(
  NAME itkQuasiNewtonOptimizerv4Test
  COMMAND
    ITKOptimizersv4TestDriver
    itkQuasiNewtonOptimizerv4Test
)

itk_add_test(
  NAME itkRegistrationParameterScalesFromIndexShiftTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkRegistrationParameterScalesFromIndexShiftTest
)

itk_add_test(
  NAME itkRegistrationParameterScalesFromPhysicalShiftPointSetTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkRegistrationParameterScalesFromPhysicalShiftPointSetTest
)

itk_add_test(
  NAME itkObjectToObjectMetricBaseTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkObjectToObjectMetricBaseTest
)

itk_add_test(
  NAME itkLBFGSOptimizerv4Test
  COMMAND
    ITKOptimizersv4TestDriver
    itkLBFGSOptimizerv4Test
)

itk_add_test(
  NAME itkLBFGSBOptimizerv4Test
  COMMAND
    ITKOptimizersv4TestDriver
    itkLBFGSBOptimizerv4Test
)

itk_add_test(
  NAME itkPowellOptimizerv4Test
  COMMAND
    ITKOptimizersv4TestDriver
    itkPowellOptimizerv4Test
    10
    0.01
    0.1
    100
    100
    0
    0.0
)

itk_add_test(
  NAME itkOnePlusOneEvolutionaryOptimizerv4Test
  COMMAND
    ITKOptimizersv4TestDriver
    itkOnePlusOneEvolutionaryOptimizerv4Test
)

itk_add_test(
  NAME itkRegularStepGradientDescentOptimizerv4Test
  COMMAND
    ITKOptimizersv4TestDriver
    itkRegularStepGradientDescentOptimizerv4Test
)
