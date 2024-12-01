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


#include "itkAntiAliasBinaryImageFilter.h"
#include "itkBinaryMask3DMeshSource.h"
#include "itkBinaryMinMaxCurvatureFlowImageFilter.h"
#include "itkCannySegmentationLevelSetImageFilter.h"
#include "itkConnectedRegionsMeshFilter.h"
#include "itkDemonsRegistrationFilter.h"
#include "itkExtensionVelocitiesImageFilter.h"

int
main(int, char *[])
{
  using InputType = itk::Image<float, 2>;
  using InputType3D = itk::Image<float, 3>;
  using OutputType = itk::Image<float, 2>;

  using MeshType = itk::Mesh<double>;

  using VectorType = itk::Vector<float, 2>;
  using VectorImageType = itk::Image<VectorType, 2>;

  itk::AntiAliasBinaryImageFilter<InputType, OutputType>::Pointer const AntiAliasBinaryImageFilterObj =
    itk::AntiAliasBinaryImageFilter<InputType, OutputType>::New();
  std::cout << "-------------AntiAliasBinaryImageFilter " << AntiAliasBinaryImageFilterObj;

  itk::BinaryMask3DMeshSource<InputType3D, MeshType>::Pointer const BinaryMask3DMeshSourceObj =
    itk::BinaryMask3DMeshSource<InputType3D, MeshType>::New();
  std::cout << "-------------BinaryMask3DMeshSource " << BinaryMask3DMeshSourceObj;

  itk::BinaryMinMaxCurvatureFlowFunction<InputType>::Pointer const BinaryMinMaxCurvatureFlowFunctionObj =
    itk::BinaryMinMaxCurvatureFlowFunction<InputType>::New();
  std::cout << "-------------BinaryMinMaxCurvatureFlowFunction " << BinaryMinMaxCurvatureFlowFunctionObj;

  itk::BinaryMinMaxCurvatureFlowImageFilter<InputType, OutputType>::Pointer const
    BinaryMinMaxCurvatureFlowImageFilterObj = itk::BinaryMinMaxCurvatureFlowImageFilter<InputType, OutputType>::New();
  std::cout << "-------------BinaryMinMaxCurvatureFlowImageFilter " << BinaryMinMaxCurvatureFlowImageFilterObj;

  itk::CannySegmentationLevelSetFunction<InputType, InputType>::Pointer const CannySegmentationLevelSetFunctionObj =
    itk::CannySegmentationLevelSetFunction<InputType, InputType>::New();
  std::cout << "-------------CannySegmentationLevelSetFunction " << CannySegmentationLevelSetFunctionObj;

  itk::CannySegmentationLevelSetImageFilter<InputType, OutputType>::Pointer const
    CannySegmentationLevelSetImageFilterObj = itk::CannySegmentationLevelSetImageFilter<InputType, OutputType>::New();
  std::cout << "-------------CannySegmentationLevelSetImageFilter " << CannySegmentationLevelSetImageFilterObj;

  itk::ConnectedRegionsMeshFilter<MeshType, MeshType>::Pointer const ConnectedRegionsMeshFilterObj =
    itk::ConnectedRegionsMeshFilter<MeshType, MeshType>::New();
  std::cout << "-------------ConnectedRegionsMeshFilter " << ConnectedRegionsMeshFilterObj;

  itk::CurvatureFlowFunction<InputType>::Pointer const CurvatureFlowFunctionObj =
    itk::CurvatureFlowFunction<InputType>::New();
  std::cout << "-------------CurvatureFlowFunction " << CurvatureFlowFunctionObj;

  itk::CurvatureFlowImageFilter<InputType, OutputType>::Pointer const CurvatureFlowImageFilterObj =
    itk::CurvatureFlowImageFilter<InputType, OutputType>::New();
  std::cout << "-------------CurvatureFlowImageFilter " << CurvatureFlowImageFilterObj;

  itk::DemonsRegistrationFilter<InputType, OutputType, VectorImageType>::Pointer const DemonsRegistrationFilterObj =
    itk::DemonsRegistrationFilter<InputType, OutputType, VectorImageType>::New();
  std::cout << "-------------DemonsRegistrationFilter " << DemonsRegistrationFilterObj;

  itk::DemonsRegistrationFunction<InputType, OutputType, VectorImageType>::Pointer const DemonsRegistrationFunctionObj =
    itk::DemonsRegistrationFunction<InputType, OutputType, VectorImageType>::New();
  std::cout << "-------------DemonsRegistrationFunction " << DemonsRegistrationFunctionObj;

  itk::ExtensionVelocitiesImageFilter<InputType, float, 1>::Pointer const ExtensionVelocitiesImageFilterObj =
    itk::ExtensionVelocitiesImageFilter<InputType, float, 1>::New();
  std::cout << "-------------ExtensionVelocitiesImageFilter " << ExtensionVelocitiesImageFilterObj;

  //  itk::fem::FEMRegistrationFilter<InputType,InputType>::Pointer FEMRegistrationFilterObj =
  //    itk::fem::FEMRegistrationFilter<InputType,InputType>::New();
  //  std:: cout << "-------------FEMRegistrationFilter " << FEMRegistrationFilterObj;

  itk::FastMarchingExtensionImageFilter<InputType, float>::Pointer const FastMarchingExtensionImageFilterObj =
    itk::FastMarchingExtensionImageFilter<InputType, float>::New();
  std::cout << "-------------FastMarchingExtensionImageFilter " << FastMarchingExtensionImageFilterObj;

  itk::FastMarchingImageFilter<InputType>::Pointer const FastMarchingImageFilterObj =
    itk::FastMarchingImageFilter<InputType>::New();
  std::cout << "-------------FastMarchingImageFilter " << FastMarchingImageFilterObj;

  return EXIT_SUCCESS;
}
