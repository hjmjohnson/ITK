itk_module_test()
set(
  ITKOptimizersTests
  itkInitializationBiasedParticleSwarmOptimizerTest.cxx
  itkLevenbergMarquardtOptimizerTest.cxx
  itkPowellOptimizerTest.cxx
  itkVersorRigid3DTransformOptimizerTest.cxx
  itkVersorTransformOptimizerTest.cxx
)

createtestdriver(ITKOptimizers "${ITKOptimizers-Test_LIBRARIES}" "${ITKOptimizersTests}")

itk_add_test(
  NAME itkPowellOptimizerTest
  COMMAND
    ITKOptimizersTestDriver
    itkPowellOptimizerTest
    0
    10
    0.01
    0.1
    100
    100
    0
    0.0
)
itk_add_test(
  NAME itkVersorTransformOptimizerTest
  COMMAND
    ITKOptimizersTestDriver
    itkVersorTransformOptimizerTest
)
itk_add_test(
  NAME itkLevenbergMarquardtOptimizerTest
  COMMAND
    ITKOptimizersTestDriver
    itkLevenbergMarquardtOptimizerTest
)
itk_add_test(
  NAME itkVersorRigid3DTransformOptimizerTest
  COMMAND
    ITKOptimizersTestDriver
    itkVersorRigid3DTransformOptimizerTest
)
itk_add_test(
  NAME itkInitializationBiasedParticleSwarmOptimizerTest
  COMMAND
    ITKOptimizersTestDriver
    itkInitializationBiasedParticleSwarmOptimizerTest
    0.7298
    1.49609
    1.49609
    1.49609
)

set(
  ITKOptimizersGTests
  itkAmoebaOptimizerGTest.cxx
  itkConjugateGradientOptimizerGTest.cxx
  itkCumulativeGaussianOptimizerGTest.cxx
  itkExhaustiveOptimizerGTest.cxx
  itkFRPROptimizerGTest.cxx
  itkGradientDescentOptimizerGTest.cxx
  itkLBFGSBOptimizerGTest.cxx
  itkLBFGSOptimizerGTest.cxx
  itkLevenbergMarquardtOptimizerGTest.cxx
  itkOnePlusOneEvolutionaryOptimizerGTest.cxx
  itkOptimizersHierarchyGTest.cxx
  itkParticleSwarmOptimizerGTest.cxx
  itkRegularStepGradientDescentOptimizerGTest.cxx
  itkSPSAOptimizerGTest.cxx
)
creategoogletestdriver(ITKOptimizers "${ITKOptimizers-Test_LIBRARIES}" "${ITKOptimizersGTests}")
