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

#include "itkArrowSpatialObject.h"
#include "itkBlobSpatialObject.h"
#include "itkBoxSpatialObject.h"
#include "itkContourSpatialObject.h"
#include "itkDTITubeSpatialObject.h"
#include "itkEllipseSpatialObject.h"
#include "itkGaussianSpatialObject.h"
#include "itkGroupSpatialObject.h"
#include "itkImageMaskSpatialObject.h"
#include "itkImageSpatialObject.h"
#include "itkLandmarkSpatialObject.h"
#include "itkLineSpatialObject.h"
#include "itkMeshSpatialObject.h"
#include "itkPolygonSpatialObject.h"
#include "itkSurfaceSpatialObject.h"
#include "itkTubeSpatialObject.h"
#include "itkTubeSpatialObjectPoint.h"

int
itkSpatialObjectPrintTest(int, char *[])
{
  itk::ArrowSpatialObject<3>::Pointer const ArrowSpatialObjectObj = itk::ArrowSpatialObject<3>::New();
  std::cout << "----------ArrowSpatialObject " << ArrowSpatialObjectObj;

  itk::BlobSpatialObject<3>::Pointer const BlobSpatialObjectObj = itk::BlobSpatialObject<3>::New();
  std::cout << "----------BlobSpatialObject " << BlobSpatialObjectObj;

  itk::BoxSpatialObject<3>::Pointer const BoxSpatialObjectObj = itk::BoxSpatialObject<3>::New();
  std::cout << "----------BoxSpatialObject " << BoxSpatialObjectObj;

  itk::ContourSpatialObject<3>::Pointer const ContourSpatialObjectObj = itk::ContourSpatialObject<3>::New();
  std::cout << "----------ContourSpatialObject " << ContourSpatialObjectObj;

  itk::DTITubeSpatialObject<3>::Pointer const DTITubeSpatialObjectObj = itk::DTITubeSpatialObject<3>::New();
  std::cout << "----------DTITubeSpatialObject " << DTITubeSpatialObjectObj;

  itk::EllipseSpatialObject<3>::Pointer const EllipseSpatialObjectObj = itk::EllipseSpatialObject<3>::New();
  std::cout << "----------EllipseSpatialObject " << EllipseSpatialObjectObj;

  itk::GaussianSpatialObject<3>::Pointer const GaussianSpatialObjectObj = itk::GaussianSpatialObject<3>::New();
  std::cout << "----------GaussianSpatialObject " << GaussianSpatialObjectObj;

  itk::GroupSpatialObject<3>::Pointer const GroupSpatialObjectObj = itk::GroupSpatialObject<3>::New();
  std::cout << "----------GroupSpatialObject " << GroupSpatialObjectObj;

  itk::ImageMaskSpatialObject<3>::Pointer const ImageMaskSpatialObjectObj = itk::ImageMaskSpatialObject<3>::New();
  std::cout << "----------ImageMaskSpatialObject " << ImageMaskSpatialObjectObj;

  using Pixel = unsigned short;
  itk::ImageSpatialObject<3, Pixel>::Pointer const ImageSpatialObjectObj = itk::ImageSpatialObject<3, Pixel>::New();
  std::cout << "----------ImageSpatialObject " << ImageSpatialObjectObj;

  itk::LandmarkSpatialObject<3>::Pointer const LandmarkSpatialObjectObj = itk::LandmarkSpatialObject<3>::New();
  std::cout << "----------LandmarkSpatialObject " << LandmarkSpatialObjectObj;

  itk::LineSpatialObject<3>::Pointer const LineSpatialObjectObj = itk::LineSpatialObject<3>::New();
  std::cout << "----------LineSpatialObject " << LineSpatialObjectObj;

  auto * LineSpatialObjectPointObj = new itk::LineSpatialObjectPoint<3>;
  std::cout << "----------LineSpatialObjectPoint " << LineSpatialObjectPointObj;
  delete LineSpatialObjectPointObj;

  itk::MeshSpatialObject<>::Pointer const MeshSpatialObjectObj = itk::MeshSpatialObject<>::New();
  std::cout << "----------MeshSpatialObject " << MeshSpatialObjectObj;

  itk::PolygonSpatialObject<3>::Pointer const PolygonSpatialObjectObj = itk::PolygonSpatialObject<3>::New();
  std::cout << "----------PolygonSpatialObject " << PolygonSpatialObjectObj;

  itk::SpatialObject<3>::Pointer const SpatialObjectObj = itk::SpatialObject<3>::New();
  std::cout << "----------SpatialObject " << SpatialObjectObj;

  auto * SpatialObjectPointObj = new itk::SpatialObjectPoint<3>;
  std::cout << "----------SpatialObjectPoint ";
  SpatialObjectPointObj->Print(std::cout);
  delete SpatialObjectPointObj;

  itk::SpatialObjectProperty const SpatialObjectPropertyObj;
  std::cout << "----------SpatialObjectProperty ";
  SpatialObjectPropertyObj.Print(std::cout);

  itk::SurfaceSpatialObject<3>::Pointer const SurfaceSpatialObjectObj = itk::SurfaceSpatialObject<3>::New();
  std::cout << "----------SurfaceSpatialObject " << SurfaceSpatialObjectObj;

  itk::SurfaceSpatialObjectPoint<3> const SurfaceSpatialObjectPointObj;
  std::cout << "----------SurfaceSpatialObjectPoint ";
  SurfaceSpatialObjectPointObj.Print(std::cout);

  itk::TubeSpatialObject<3>::Pointer const TubeSpatialObjectObj = itk::TubeSpatialObject<3>::New();
  std::cout << "----------TubeSpatialObject " << TubeSpatialObjectObj;

  itk::TubeSpatialObjectPoint<3> const TubeSpatialObjectPointObj;
  std::cout << "----------TubeSpatialObjectPoint ";
  TubeSpatialObjectPointObj.Print(std::cout);

  return 0;
}
