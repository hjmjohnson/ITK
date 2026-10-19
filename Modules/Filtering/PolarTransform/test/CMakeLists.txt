itk_module_test()

set(PolarTransformGTests itkPolarTransformGTest.cxx)
creategoogletestdriver(PolarTransform "${PolarTransform-Test_LIBRARIES}" "${PolarTransformGTests}")

if(ITK_WRAP_PYTHON)
  itk_python_expression_add_test(
    NAME itkPolarToCartesianTransformPythonTest
    EXPRESSION "instance = itk.PolarToCartesianTransform.New()"
  )
  itk_python_expression_add_test(
    NAME itkCartesianToPolarTransformPythonTest
    EXPRESSION "instance = itk.CartesianToPolarTransform.New()"
  )
endif()
