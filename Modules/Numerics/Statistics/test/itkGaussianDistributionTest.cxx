/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkGaussianDistribution.h"
#include "itkTestingMacros.h"
#include "itkStdStreamStateSave.h"
#include "itkMath.h"

int
itkGaussianDistributionTest(int, char *[])
{
  // Save the format stream variables for std::cout
  // They will be restored when coutState goes out of scope
  const itk::StdStreamStateSave coutState(std::cout);

  std::cout << "itkGaussianDistribution Test \n \n";

  using DistributionType = itk::Statistics::GaussianDistribution;

  auto distributionFunction = DistributionType::New();

  std::cout << "GetNameOfClass() = " << distributionFunction->GetNameOfClass() << '\n';
  std::cout << "HasMean()        = " << distributionFunction->HasMean() << '\n';
  std::cout << "HasVariance()    = " << distributionFunction->HasVariance() << '\n';
  std::cout << "Number of parameters = " << distributionFunction->GetNumberOfParameters() << '\n';

  distributionFunction->Print(std::cout);

  int    i;
  double x;
  double value;
  double diff;

  int status = EXIT_SUCCESS;

  // Tolerance for the values.
  const double tol = 1e-8;
  std::cout << "Tolerance used for test: ";
  std::cout.width(22);
  std::cout.precision(15);
  std::cout << tol << '\n';
  std::cout << '\n';

  // expected values for Gaussian cdf with mean 0 and variance 1 at
  // values of -5:1:5
  const double expected1[] = { 2.866515718791942e-007, 3.167124183311998e-005, 1.349898031630095e-003,
                               2.275013194817922e-002, 1.586552539314571e-001, 5.000000000000000e-001,
                               8.413447460685429e-001, 9.772498680518208e-001, 9.986501019683699e-001,
                               9.999683287581669e-001, 9.999997133484281e-001 };

  std::cout << "Gaussian CDF" << '\n';
  for (i = -5; i <= 5; ++i)
  {
    x = static_cast<double>(i);

    value = distributionFunction->EvaluateCDF(x);

    diff = itk::Math::abs(value - expected1[i + 5]);

    std::cout << "Gaussian cdf at ";
    std::cout.width(2);
    std::cout << x << " = ";
    std::cout.width(22);
    std::cout << value << ", expected value = ";
    std::cout.width(22);
    std::cout << expected1[i + 5] << ", error = ";
    std::cout.width(22);
    std::cout << diff;
    if (diff < tol)
    {
      std::cout << ", Passed." << '\n';
    }
    else
    {
      std::cout << ", Failed." << '\n';
      status = EXIT_FAILURE;
    }
  }
  std::cout << '\n';


  std::cout << "Inverse Gaussian CDF" << '\n';
  for (i = -5; i <= 5; ++i)
  {
    value = distributionFunction->EvaluateInverseCDF(expected1[i + 5]);

    diff = itk::Math::abs(value - static_cast<double>(i));

    std::cout << "Inverse Gaussian cdf at ";
    std::cout.width(22);
    std::cout << expected1[i + 5] << " = ";
    std::cout.width(22);
    std::cout << value << ", expected value = ";
    std::cout.width(22);
    std::cout << static_cast<double>(i) << ", error = ";
    std::cout.width(22);
    std::cout << diff;
    if (diff < tol)
    {
      std::cout << ", Passed." << '\n';
    }
    else
    {
      std::cout << ", Failed." << '\n';
      status = EXIT_FAILURE;
    }
  }
  std::cout << '\n';

  // do the same tests at a different mean/variance
  distributionFunction->SetMean(5.0);
  distributionFunction->SetVariance(2.0);

  std::cout << "Testing mean = " << distributionFunction->GetMean()
            << ", variance = " << distributionFunction->GetVariance() << '\n';

  const double expected2[] = { 7.687298972140230e-013, 9.830802207714426e-011, 7.708628950140045e-009,
                               3.715491861707074e-007, 1.104524849929275e-005, 2.034760087224798e-004,
                               2.338867490523635e-003, 1.694742676234465e-002, 7.864960352514258e-002,
                               2.397500610934768e-001, 5.000000000000000e-001 };

  std::cout << "Gaussian CDF" << '\n';
  for (i = -5; i <= 5; ++i)
  {
    x = static_cast<double>(i);

    value = distributionFunction->EvaluateCDF(x);

    diff = itk::Math::abs(value - expected2[i + 5]);

    std::cout << "Gaussian cdf at ";
    std::cout.width(2);
    std::cout << x << " = ";
    std::cout.width(22);
    std::cout << value << ", expected value = ";
    std::cout.width(22);
    std::cout << expected2[i + 5] << ", error = ";
    std::cout.width(22);
    std::cout << diff;
    if (diff < tol)
    {
      std::cout << ", Passed." << '\n';
    }
    else
    {
      std::cout << ", Failed." << '\n';
      status = EXIT_FAILURE;
    }
  }
  std::cout << '\n';

  // same test but using the parameter vector API
  DistributionType::ParametersType params(2);
  params[0] = 5.0;
  params[1] = 2.0;

  std::cout << "Testing mean = " << params[0] << ", variance = " << params[1] << '\n';

  distributionFunction->SetMean(0.0);     // clear settings
  distributionFunction->SetVariance(1.0); // clear settings

  const double expected3[] = { 7.687298972140230e-013, 9.830802207714426e-011, 7.708628950140045e-009,
                               3.715491861707074e-007, 1.104524849929275e-005, 2.034760087224798e-004,
                               2.338867490523635e-003, 1.694742676234465e-002, 7.864960352514258e-002,
                               2.397500610934768e-001, 5.000000000000000e-001 };

  std::cout << "Gaussian CDF (parameter vector API)" << '\n';
  for (i = -5; i <= 5; ++i)
  {
    x = static_cast<double>(i);

    value = distributionFunction->EvaluateCDF(x, params);

    diff = itk::Math::abs(value - expected3[i + 5]);

    std::cout << "Gaussian cdf at ";
    std::cout.width(2);
    std::cout << x << " = ";
    std::cout.width(22);
    std::cout << value << ", expected value = ";
    std::cout.width(22);
    std::cout << expected3[i + 5] << ", error = ";
    std::cout.width(22);
    std::cout << diff;
    if (diff < tol)
    {
      std::cout << ", Passed." << '\n';
    }
    else
    {
      std::cout << ", Failed." << '\n';
      status = EXIT_FAILURE;
    }
  }
  std::cout << '\n';

  // same test but using the separate parameters
  std::cout << "Testing mean = " << params[0] << ", variance = " << params[1] << '\n';

  const double expected4[] = { 7.687298972140230e-013, 9.830802207714426e-011, 7.708628950140045e-009,
                               3.715491861707074e-007, 1.104524849929275e-005, 2.034760087224798e-004,
                               2.338867490523635e-003, 1.694742676234465e-002, 7.864960352514258e-002,
                               2.397500610934768e-001, 5.000000000000000e-001 };

  std::cout << "Gaussian CDF (separate parameter API)" << '\n';
  for (i = -5; i <= 5; ++i)
  {
    x = static_cast<double>(i);

    value = distributionFunction->EvaluateCDF(x, params[0], params[1]);

    diff = itk::Math::abs(value - expected4[i + 5]);

    std::cout << "Gaussian cdf at ";
    std::cout.width(2);
    std::cout << x << " = ";
    std::cout.width(22);
    std::cout << value << ", expected value = ";
    std::cout.width(22);
    std::cout << expected4[i + 5] << ", error = ";
    std::cout.width(22);
    std::cout << diff;
    if (diff < tol)
    {
      std::cout << ", Passed." << '\n';
    }
    else
    {
      std::cout << ", Failed." << '\n';
      status = EXIT_FAILURE;
    }
  }
  std::cout << '\n';

  std::cout << "Inverse Gaussian CDF" << '\n';
  // put the parameters back
  distributionFunction->SetParameters(params);
  for (i = -5; i <= 5; ++i)
  {
    value = distributionFunction->EvaluateInverseCDF(expected2[i + 5]);

    diff = itk::Math::abs(value - static_cast<double>(i));

    std::cout << "Inverse Gaussian cdf at ";
    std::cout.width(22);
    std::cout << expected2[i + 5] << " = ";
    std::cout.width(22);
    std::cout << value << ", expected value = ";
    std::cout.width(22);
    std::cout << static_cast<double>(i) << ", error = ";
    std::cout.width(22);
    std::cout << diff;
    if (diff < tol)
    {
      std::cout << ", Passed." << '\n';
    }
    else
    {
      std::cout << ", Failed." << '\n';
      status = EXIT_FAILURE;
    }
  }
  std::cout << '\n';

  constexpr double mean1 = 1.0;
  constexpr double variance1 = 2.5;

  DistributionType::ParametersType parameters(distributionFunction->GetNumberOfParameters());
  parameters[0] = mean1;
  parameters[1] = variance1;
  distributionFunction->SetParameters(parameters);
  x = .1;
  std::cout << "Parameters = " << parameters << '\n';
  std::cout << "Variance() = " << distributionFunction->GetVariance() << '\n';
  std::cout << "PDF(x,p) = " << distributionFunction->PDF(x, parameters) << '\n';
  std::cout << "EvaluatePDF(x) = " << distributionFunction->EvaluatePDF(x) << '\n';
  std::cout << "EvaluatePDF(x,p) = " << distributionFunction->EvaluatePDF(x, parameters) << '\n';
  std::cout << "EvaluatePDF(x,m,v) = " << distributionFunction->EvaluatePDF(x, mean1, variance1) << '\n';
  std::cout << "CDF(x,p) = " << distributionFunction->CDF(x, parameters) << '\n';
  std::cout << "EvaluateCDF(x,p) = " << distributionFunction->EvaluateCDF(x, parameters) << '\n';
  std::cout << "InverseCDF(x,p) = " << distributionFunction->InverseCDF(x, parameters) << '\n';
  std::cout << "InverseCDF(x,mean,variance) = " << distributionFunction->InverseCDF(x, mean1, variance1) << '\n';
  std::cout << "EvaluateInverseCDF(x) = " << distributionFunction->EvaluateInverseCDF(x) << '\n';
  std::cout << "EvaluateInverseCDF(x,p) = " << distributionFunction->EvaluateInverseCDF(x, parameters) << '\n';
  std::cout << "EvaluateInverseCDF(x,m,v) = " << distributionFunction->EvaluateInverseCDF(x, mean1, variance1) << '\n';

  std::cout << "InverseCDF(10.0,p) = " << distributionFunction->InverseCDF(10.0, parameters) << '\n';
  std::cout << "InverseCDF(10.0,mean,variance) = " << distributionFunction->InverseCDF(10.0, mean1, variance1) << '\n';
  std::cout << "EvaluateInverseCDF(10.0) = " << distributionFunction->EvaluateInverseCDF(10.0) << '\n';
  std::cout << "EvaluateInverseCDF(10.0,p) = " << distributionFunction->EvaluateInverseCDF(10.0, parameters) << '\n';
  std::cout << "EvaluateInverseCDF(10.0,m,v) = " << distributionFunction->EvaluateInverseCDF(10.0, mean1, variance1)
            << '\n';

  std::cout << "InverseCDF(-10.0,p) = " << distributionFunction->InverseCDF(-10.0, parameters) << '\n';
  std::cout << "InverseCDF(-10.0,mean,variance) = " << distributionFunction->InverseCDF(-10.0, mean1, variance1)
            << '\n';
  std::cout << "EvaluateInverseCDF(-10.0) = " << distributionFunction->EvaluateInverseCDF(-10.0) << '\n';
  std::cout << "EvaluateInverseCDF(-10.0,p) = " << distributionFunction->EvaluateInverseCDF(-10.0, parameters) << '\n';
  std::cout << "EvaluateInverseCDF(-10.0,m,v) = " << distributionFunction->EvaluateInverseCDF(-10.0, mean1, variance1)
            << '\n';

  const unsigned int               wrongNumberOfParameters = distributionFunction->GetNumberOfParameters() * 42;
  DistributionType::ParametersType wrongParameters(wrongNumberOfParameters);
  wrongParameters.Fill(1.0);
  distributionFunction->SetParameters(wrongParameters);

  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->GetVariance());
  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->GetMean());
  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->PDF(x, wrongParameters));
  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->EvaluatePDF(x));
  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->EvaluatePDF(x, wrongParameters));
  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->EvaluateCDF(x));
  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->EvaluateCDF(x, wrongParameters));
  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->EvaluateInverseCDF(x));
  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->EvaluateInverseCDF(x, wrongParameters));
  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->CDF(x, wrongParameters));
  ITK_TRY_EXPECT_EXCEPTION(distributionFunction->InverseCDF(x, wrongParameters));

  distributionFunction->SetParameters(wrongParameters);
  const double newMean = 17.0;
  distributionFunction->SetMean(newMean);
  ITK_TEST_SET_GET_VALUE(newMean, distributionFunction->GetMean());

  distributionFunction->SetParameters(wrongParameters);
  const double newVariance = 42.0;
  distributionFunction->SetVariance(newVariance);
  ITK_TEST_SET_GET_VALUE(newVariance, distributionFunction->GetVariance());

  constexpr double mean2 = 0.0;
  constexpr double variance2 = 1.0;

  parameters[0] = mean2;
  parameters[1] = variance2;

  distributionFunction->SetParameters(parameters);

  std::cout << "Parameters = " << parameters << '\n';
  std::cout << "Variance() = " << distributionFunction->GetVariance() << '\n';
  std::cout << "PDF(x,p) = " << distributionFunction->PDF(x, parameters) << '\n';
  std::cout << "EvaluatePDF(x) = " << distributionFunction->EvaluatePDF(x) << '\n';
  std::cout << "EvaluatePDF(x,p) = " << distributionFunction->EvaluatePDF(x, parameters) << '\n';
  std::cout << "EvaluatePDF(x,m,v) = " << distributionFunction->EvaluatePDF(x, mean2, variance2) << '\n';
  std::cout << "CDF(x,p) = " << distributionFunction->CDF(x, parameters) << '\n';
  std::cout << "EvaluateCDF(x,p) = " << distributionFunction->EvaluateCDF(x, parameters) << '\n';
  std::cout << "EvaluateCDF(x,m,v) = " << distributionFunction->EvaluateCDF(x, mean2, variance2) << '\n';
  std::cout << "InverseCDF(x,p) = " << distributionFunction->InverseCDF(x, parameters) << '\n';
  std::cout << "EvaluateInverseCDF(x,p) = " << distributionFunction->EvaluateInverseCDF(x, parameters) << '\n';
  std::cout << "EvaluateInverseCDF(x,m,v) = " << distributionFunction->EvaluateInverseCDF(x, mean2, variance2) << '\n';

  const DistributionType::ParametersType parameters0(0);
  distributionFunction->SetParameters(parameters0);
  distributionFunction->Print(std::cout);

  DistributionType::ParametersType parameters1(1);
  parameters1.Fill(1.0);
  distributionFunction->SetParameters(parameters1);
  distributionFunction->Print(std::cout);

  return status;
}
