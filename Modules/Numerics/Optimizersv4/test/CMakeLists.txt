itk_module_test()
set(
  ITKOptimizersv4Tests
  itkAutoScaledGradientDescentRegistrationOnVectorTest.cxx
  itkAutoScaledGradientDescentRegistrationTest.cxx
  itkMultiGradientOptimizerv4Test.cxx
  itkPowellOptimizerv4Test.cxx
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
  itkLBFGSBOptimizerv4GTest.cxx
  itkLBFGSOptimizerv4GTest.cxx
  itkMultiGradientOptimizerv4GTest.cxx
  itkMultiStartOptimizerv4GTest.cxx
  itkObjectToObjectMetricBaseGTest.cxx
  itkObjectToObjectOptimizerBaseGTest.cxx
  itkOnePlusOneEvolutionaryOptimizerv4GTest.cxx
  itkOptimizerParameterScalesEstimatorGTest.cxx
  itkQuasiNewtonOptimizerv4GTest.cxx
  itkRegistrationParameterScalesEstimatorGTest.cxx
  itkRegistrationParameterScalesFromIndexShiftGTest.cxx
  itkRegistrationParameterScalesFromJacobianGTest.cxx
  itkRegistrationParameterScalesFromPhysicalShiftPointSetGTest.cxx
  itkWindowConvergenceMonitoringFunctionGTest.cxx
)
creategoogletestdriver(ITKOptimizersv4 "${ITKOptimizersv4-Test_LIBRARIES}" "${ITKOptimizersv4GTests}")

itk_add_test(
  NAME itkMultiGradientOptimizerv4Test
  COMMAND
    ITKOptimizersv4TestDriver
    itkMultiGradientOptimizerv4Test
)

itk_add_test(
  NAME itkRegistrationParameterScalesFromPhysicalShiftTest
  COMMAND
    ITKOptimizersv4TestDriver
    itkRegistrationParameterScalesFromPhysicalShiftTest
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
  NAME itkRegularStepGradientDescentOptimizerv4Test
  COMMAND
    ITKOptimizersv4TestDriver
    itkRegularStepGradientDescentOptimizerv4Test
)
