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


#include "itkAcosImageAdaptor.h"
#include "itkAddImageAdaptor.h"
#include "itkAsinImageAdaptor.h"
#include "itkAtanImageAdaptor.h"
#include "itkAzimuthElevationToCartesianTransform.h"
#include "itkBSplineTransform.h"
#include "itkBSplineDerivativeKernelFunction.h"
#include "itkCenteredAffineTransform.h"
#include "itkCenteredRigid2DTransform.h"
#include "itkCenteredTransformInitializer.h"
#include "itkCentralDifferenceImageFunction.h"
#include "itkColorTable.h"
#include "itkConicShellInteriorExteriorSpatialFunction.h"
#include "itkCosImageAdaptor.h"
#include "itkElasticBodyReciprocalSplineKernelTransform.h"
#include "itkElasticBodySplineKernelTransform.h"
#include "itkEllipsoidInteriorExteriorSpatialFunction.h"
#include "itkEquivalencyTable.h"
#include "itkEuler2DTransform.h"
#include "itkEuler3DTransform.h"
#include "itkExpImageAdaptor.h"
#include "itkExpNegativeImageAdaptor.h"
#include "itkFiniteCylinderSpatialFunction.h"
#include "itkFrustumSpatialFunction.h"
#include "itkGaussianDerivativeImageFunction.h"
#include "itkGaussianKernelFunction.h"
#include "itkIdentityTransform.h"
#include "itkImageRegionSplitterMultidimensional.h"
#include "itkKLMSegmentationRegion.h"
#include "itkLevelSetFunction.h"
#include "itkLightProcessObject.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkLog10ImageAdaptor.h"
#include "itkLogImageAdaptor.h"
#include "itkMatrixResizeableDataObject.h"
#include "itkMaximumDecisionRule.h"
#include "itkMaximumRatioDecisionRule.h"
#include "itkMeanImageFunction.h"
#include "itkMedianImageFunction.h"
#include "itkMesh.h"
#include "itkMeshToMeshFilter.h"
#include "itkMinimumDecisionRule.h"
#include "itkMultiThreaderBase.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "itkNeighborhoodBinaryThresholdImageFunction.h"
#include "itkNthElementImageAdaptor.h"
#include "itkObjectStore.h"
#include "itkOneWayEquivalencyTable.h"
#include "itkProgressAccumulator.h"
#include "itkQuaternionRigidTransform.h"
#include "itkRGBToVectorImageAdaptor.h"
#include "itkRigid3DPerspectiveTransform.h"
#include "itkScaleSkewVersor3DTransform.h"
#include "itkScaleTransform.h"
#include "itkSimilarity2DTransform.h"
#include "itkSinImageAdaptor.h"
#include "itkSphereSpatialFunction.h"
#include "itkSqrtImageAdaptor.h"
#include "itkSymmetricEllipsoidInteriorExteriorSpatialFunction.h"
#include "itkTanImageAdaptor.h"
#include "itkTextOutput.h"
#include "itkThinPlateR2LogRSplineKernelTransform.h"
#include "itkThinPlateSplineKernelTransform.h"
#include "itkTorusInteriorExteriorSpatialFunction.h"
#include "itkTranslationTransform.h"
#include "itkValarrayImageContainer.h"
#include "itkVarianceImageFunction.h"
#include "itkVectorLinearInterpolateImageFunction.h"
#include "itkVectorToRGBImageAdaptor.h"
#include "itkVectorImage.h"
#include "itkVersion.h"
#include "itkVolumeSplineKernelTransform.h"
#include "itkXMLFileOutputWindow.h"
#include "itkRedPixelAccessor.h"

struct TestObject
{
  float vector[3];
  int   counter;
};


int
itkCommonPrintTest(int, char *[])
{
  using InputType = itk::Image<float, 2>;
  using OutputType = itk::Image<float, 2>;

  using Point3DType = itk::Point<float, 3>;
  using PointType = itk::Point<float, 2>;
  using MeshType = itk::Mesh<PointType>;

  using VectorType = itk::Vector<float, 2>;
  using VectorImageType = itk::Image<VectorType, 2>;

  using RGBPixelType = itk::RGBPixel<unsigned short>;
  using RGBImageType = itk::Image<RGBPixelType, 2>;

  // Used for CenteredTransformInitializer
  using TransformType = itk::CenteredRigid2DTransform<float>;


  // Used for ImageAdaptor
  using RedAccessorType = itk::RedPixelAccessor<float>;

  itk::AcosImageAdaptor<InputType, InputType>::Pointer const AcosImageAdaptorObj =
    itk::AcosImageAdaptor<InputType, InputType>::New();
  std::cout << "------------AcosImageAdaptor" << AcosImageAdaptorObj;

  itk::AddImageAdaptor<InputType>::Pointer const AddImageAdaptorObj = itk::AddImageAdaptor<InputType>::New();
  std::cout << "------------AddImageAdaptor" << AddImageAdaptorObj;

  itk::AffineTransform<float, 3>::Pointer const AffineTransformObj = itk::AffineTransform<float, 3>::New();
  std::cout << "------------AffineTransform" << AffineTransformObj;

  itk::AsinImageAdaptor<InputType, InputType>::Pointer const AsinImageAdaptorObj =
    itk::AsinImageAdaptor<InputType, InputType>::New();
  std::cout << "------------AsinImageAdaptor" << AsinImageAdaptorObj;

  itk::AtanImageAdaptor<InputType, InputType>::Pointer const AtanImageAdaptorObj =
    itk::AtanImageAdaptor<InputType, InputType>::New();
  std::cout << "------------AtanImageAdaptor" << AtanImageAdaptorObj;

  itk::AzimuthElevationToCartesianTransform<float, 3>::Pointer const AzimuthElevationToCartesianTransformObj =
    itk::AzimuthElevationToCartesianTransform<float, 3>::New();
  std::cout << "------------AzimuthElevationToCartesianTransform" << AzimuthElevationToCartesianTransformObj;

  itk::BSplineTransform<float, 3, 3>::Pointer const BSplineTransformObj = itk::BSplineTransform<float, 3, 3>::New();
  std::cout << "------------BSplineTransform" << BSplineTransformObj;

  itk::BSplineDerivativeKernelFunction<3>::Pointer const BSplineDerivativeKernelFunctionObj =
    itk::BSplineDerivativeKernelFunction<3>::New();
  std::cout << "------------BSplineDerivativeKernelFunction" << BSplineDerivativeKernelFunctionObj;

  itk::BSplineInterpolationWeightFunction<float, 2, 3>::Pointer const BSplineInterpolationWeightFunctionObj =
    itk::BSplineInterpolationWeightFunction<float, 2, 3>::New();
  std::cout << "------------BSplineInterpolationWeightFunction" << BSplineInterpolationWeightFunctionObj;

  itk::BSplineKernelFunction<3>::Pointer const BSplineKernelFunctionObj = itk::BSplineKernelFunction<3>::New();
  std::cout << "------------BSplineKernelFunction" << BSplineKernelFunctionObj;

  itk::BinaryThresholdImageFunction<InputType>::Pointer const BinaryThresholdImageFunctionObj =
    itk::BinaryThresholdImageFunction<InputType>::New();
  std::cout << "------------BinaryThresholdImageFunction" << BinaryThresholdImageFunctionObj;

  itk::BoundingBox<unsigned long>::Pointer const BoundingBoxObj = itk::BoundingBox<unsigned long>::New();
  std::cout << "------------BoundingBox" << BoundingBoxObj;

  itk::CenteredAffineTransform<double, 3>::Pointer const CenteredAffineTransformObj =
    itk::CenteredAffineTransform<double, 3>::New();
  std::cout << "------------CenteredAffineTransform" << CenteredAffineTransformObj;

  itk::CenteredRigid2DTransform<double>::Pointer const CenteredRigid2DTransformObj =
    itk::CenteredRigid2DTransform<double>::New();
  std::cout << "------------CenteredRigid2DTransform" << CenteredRigid2DTransformObj;

  itk::CenteredTransformInitializer<TransformType, InputType, InputType>::Pointer const
    CenteredTransformInitializerObj = itk::CenteredTransformInitializer<TransformType, InputType, InputType>::New();
  std::cout << "------------CenteredTransformInitializer" << CenteredTransformInitializerObj;

  itk::CentralDifferenceImageFunction<InputType>::Pointer const CentralDifferenceImageFunctionObj =
    itk::CentralDifferenceImageFunction<InputType>::New();
  std::cout << "------------CentralDifferenceImageFunction" << CentralDifferenceImageFunctionObj;

  itk::ColorTable<float>::Pointer const ColorTableObj = itk::ColorTable<float>::New();
  std::cout << "------------ColorTable" << ColorTableObj;

  itk::ConicShellInteriorExteriorSpatialFunction<3>::Pointer const ConicShellInteriorExteriorSpatialFunctionObj =
    itk::ConicShellInteriorExteriorSpatialFunction<3>::New();
  std::cout << "------------ConicShellInteriorExteriorSpatialFunction" << ConicShellInteriorExteriorSpatialFunctionObj;

  itk::CosImageAdaptor<InputType, InputType>::Pointer const CosImageAdaptorObj =
    itk::CosImageAdaptor<InputType, InputType>::New();
  std::cout << "------------CosImageAdaptor" << CosImageAdaptorObj;

  itk::ElasticBodyReciprocalSplineKernelTransform<double, 3>::Pointer const
    ElasticBodyReciprocalSplineKernelTransformObj = itk::ElasticBodyReciprocalSplineKernelTransform<double, 3>::New();
  std::cout << "------------ElasticBodyReciprocalSplineKernelTransform"
            << ElasticBodyReciprocalSplineKernelTransformObj;

  itk::ElasticBodySplineKernelTransform<double, 3>::Pointer const ElasticBodySplineKernelTransformObj =
    itk::ElasticBodySplineKernelTransform<double, 3>::New();
  std::cout << "------------ElasticBodySplineKernelTransform" << ElasticBodySplineKernelTransformObj;

  itk::EllipsoidInteriorExteriorSpatialFunction<2, PointType>::Pointer const
    EllipsoidInteriorExteriorSpatialFunctionObj = itk::EllipsoidInteriorExteriorSpatialFunction<2, PointType>::New();
  std::cout << "------------EllipsoidInteriorExteriorSpatialFunction" << EllipsoidInteriorExteriorSpatialFunctionObj;

  itk::EquivalencyTable::Pointer const EquivalencyTableObj = itk::EquivalencyTable::New();
  std::cout << "-------------EquivalencyTable " << EquivalencyTableObj;

  itk::Euler2DTransform<double>::Pointer const Euler2DTransformObj = itk::Euler2DTransform<double>::New();
  std::cout << "------------Euler2DTransform" << Euler2DTransformObj;

  itk::Euler3DTransform<double>::Pointer const Euler3DTransformObj = itk::Euler3DTransform<double>::New();
  std::cout << "------------Euler3DTransform" << Euler3DTransformObj;

  itk::ExpImageAdaptor<InputType, OutputType>::Pointer const ExpImageAdaptorObj =
    itk::ExpImageAdaptor<InputType, OutputType>::New();
  std::cout << "------------ExpImageAdaptor" << ExpImageAdaptorObj;

  itk::ExpNegativeImageAdaptor<InputType, OutputType>::Pointer const ExpNegativeImageAdaptorObj =
    itk::ExpNegativeImageAdaptor<InputType, OutputType>::New();
  std::cout << "------------ExpNegativeImageAdaptor" << ExpNegativeImageAdaptorObj;

  itk::FileOutputWindow::Pointer const FileOutputWindowObj = itk::FileOutputWindow::New();
  std::cout << "------------FileOutputWindow" << FileOutputWindowObj;

  itk::FiniteCylinderSpatialFunction<3, Point3DType>::Pointer const FiniteCylinderSpatialFunctionObj =
    itk::FiniteCylinderSpatialFunction<3, Point3DType>::New();
  std::cout << "------------FiniteCylinderSpatialFunction" << FiniteCylinderSpatialFunctionObj;

  itk::FrustumSpatialFunction<3, Point3DType>::Pointer const FrustumSpatialFunctionObj =
    itk::FrustumSpatialFunction<3, Point3DType>::New();
  std::cout << "------------FrustumSpatialFunction" << FrustumSpatialFunctionObj;

  itk::GaussianKernelFunction<double>::Pointer const GaussianKernelFunctionObj =
    itk::GaussianKernelFunction<double>::New();
  std::cout << "------------GaussianKernelFunction" << GaussianKernelFunctionObj;

  itk::GaussianSpatialFunction<float, 2, PointType>::Pointer const GaussianSpatialFunctionObj =
    itk::GaussianSpatialFunction<float, 2, PointType>::New();
  std::cout << "------------GaussianSpatialFunction" << GaussianSpatialFunctionObj;

  itk::IdentityTransform<double, 3>::Pointer const IdentityTransformObj = itk::IdentityTransform<double, 3>::New();
  std::cout << "------------IdentityTransform" << IdentityTransformObj;

  itk::Image<VectorType, 2>::Pointer const ImageObj = itk::Image<VectorType, 2>::New();
  std::cout << "------------Image" << ImageObj;

  itk::ImageAdaptor<RGBImageType, RedAccessorType>::Pointer const ImageAdaptorObj =
    itk::ImageAdaptor<RGBImageType, RedAccessorType>::New();
  std::cout << "------------ImageAdaptor" << ImageAdaptorObj;

  itk::ImageBase<3>::Pointer const ImageBaseObj = itk::ImageBase<3>::New();
  std::cout << "------------ImageBase" << ImageBaseObj;

  itk::ImageRegionSplitterMultidimensional::Pointer const ImageRegionSplitterMultidimensionalObj =
    itk::ImageRegionSplitterMultidimensional::New();
  std::cout << "------------ImageRegionSplitterMultidimensional" << ImageRegionSplitterMultidimensionalObj;

  itk::ImportImageContainer<unsigned long, PointType>::Pointer const ImportImageContainerObj =
    itk::ImportImageContainer<unsigned long, PointType>::New();
  std::cout << "------------ImportImageContainer" << ImportImageContainerObj;

  itk::KLMSegmentationBorder::Pointer const KLMSegmentationBorderObj = itk::KLMSegmentationBorder::New();
  std::cout << "------------KLMSegmentationBorder" << KLMSegmentationBorderObj;

  itk::KLMSegmentationRegion::Pointer const KLMSegmentationRegionObj = itk::KLMSegmentationRegion::New();
  std::cout << "------------KLMSegmentationRegion" << KLMSegmentationRegionObj;

  itk::KernelTransform<double, 3>::Pointer const KernelTransformObj = itk::KernelTransform<double, 3>::New();
  std::cout << "------------KernelTransform" << KernelTransformObj;

  itk::LevelSetFunction<InputType>::Pointer const LevelSetFunctionObj = itk::LevelSetFunction<InputType>::New();
  std::cout << "------------LevelSetFunction" << LevelSetFunctionObj;

  itk::LightProcessObject::Pointer const LightProcessObjectObj = itk::LightProcessObject::New();
  std::cout << "------------LightProcessObject" << LightProcessObjectObj;

  itk::LinearInterpolateImageFunction<InputType, float>::Pointer const LinearInterpolateImageFunctionObj =
    itk::LinearInterpolateImageFunction<InputType, float>::New();
  std::cout << "------------LinearInterpolateImageFunction" << LinearInterpolateImageFunctionObj;

  itk::Log10ImageAdaptor<InputType, OutputType>::Pointer const Log10ImageAdaptorObj =
    itk::Log10ImageAdaptor<InputType, OutputType>::New();
  std::cout << "------------Log10ImageAdaptor" << Log10ImageAdaptorObj;

  itk::LogImageAdaptor<InputType, OutputType>::Pointer const LogImageAdaptorObj =
    itk::LogImageAdaptor<InputType, OutputType>::New();
  std::cout << "------------LogImageAdaptor" << LogImageAdaptorObj;

  itk::MapContainer<unsigned long, PointType>::Pointer const MapContainerObj =
    itk::MapContainer<unsigned long, PointType>::New();
  std::cout << "------------MapContainer" << MapContainerObj;

  itk::MatrixResizeableDataObject<double>::Pointer const MatrixResizeableDataObjectObj =
    itk::MatrixResizeableDataObject<double>::New();
  std::cout << "------------MatrixResizeableDataObject" << MatrixResizeableDataObjectObj;

  itk::Statistics::MaximumDecisionRule::Pointer const MaximumDecisionRuleObj =
    itk::Statistics::MaximumDecisionRule::New();
  std::cout << "------------MaximumDecisionRule" << MaximumDecisionRuleObj;

  itk::Statistics::MaximumRatioDecisionRule::Pointer const MaximumRatioDecisionRuleObj =
    itk::Statistics::MaximumRatioDecisionRule::New();
  std::cout << "------------MaximumRatioDecisionRule" << MaximumRatioDecisionRuleObj;

  itk::MeanImageFunction<InputType, float>::Pointer const MeanImageFunctionObj =
    itk::MeanImageFunction<InputType, float>::New();
  std::cout << "------------MeanImageFunction" << MeanImageFunctionObj;

  itk::MedianImageFunction<InputType, float>::Pointer const MedianImageFunctionObj =
    itk::MedianImageFunction<InputType, float>::New();
  std::cout << "------------MedianImageFunction" << MedianImageFunctionObj;

  itk::Mesh<PointType, 2>::Pointer const MeshObj = itk::Mesh<PointType, 2>::New();
  std::cout << "------------Mesh" << MeshObj;

  itk::MeshSource<MeshType>::Pointer const MeshSourceObj = itk::MeshSource<MeshType>::New();
  std::cout << "------------MeshSource" << MeshSourceObj;

  itk::MeshToMeshFilter<MeshType, MeshType>::Pointer const MeshToMeshFilterObj =
    itk::MeshToMeshFilter<MeshType, MeshType>::New();
  std::cout << "------------MeshToMeshFilter" << MeshToMeshFilterObj;

  itk::Statistics::MinimumDecisionRule::Pointer const MinimumDecisionRuleObj =
    itk::Statistics::MinimumDecisionRule::New();
  std::cout << "------------MinimumDecisionRule" << MinimumDecisionRuleObj;

  itk::MultiThreaderBase::Pointer const MultiThreaderObj = itk::MultiThreaderBase::New();
  std::cout << "------------MultiThreaderBase" << MultiThreaderObj;

  itk::NearestNeighborInterpolateImageFunction<InputType, float>::Pointer const
    NearestNeighborInterpolateImageFunctionObj = itk::NearestNeighborInterpolateImageFunction<InputType, float>::New();
  std::cout << "------------NearestNeighborInterpolateImageFunction" << NearestNeighborInterpolateImageFunctionObj;

  itk::NeighborhoodBinaryThresholdImageFunction<InputType, float>::Pointer const
    NeighborhoodBinaryThresholdImageFunctionObj =
      itk::NeighborhoodBinaryThresholdImageFunction<InputType, float>::New();
  std::cout << "------------NeighborhoodBinaryThresholdImageFunction" << NeighborhoodBinaryThresholdImageFunctionObj;

  itk::NthElementImageAdaptor<InputType, PointType>::Pointer const NthElementImageAdaptorObj =
    itk::NthElementImageAdaptor<InputType, PointType>::New();
  std::cout << "------------NthElementImageAdaptor" << NthElementImageAdaptorObj;

  itk::ObjectStore<TestObject>::Pointer const ObjectStoreObj = itk::ObjectStore<TestObject>::New();
  std::cout << "------------ObjectStore" << ObjectStoreObj;

  itk::OneWayEquivalencyTable::Pointer const OneWayEquivalencyTableObj = itk::OneWayEquivalencyTable::New();
  std::cout << "-------------OneWayEquivalencyTable " << OneWayEquivalencyTableObj;

  itk::PointSet<PointType, 2>::Pointer const PointSetObj = itk::PointSet<PointType, 2>::New();
  std::cout << "------------PointSet" << PointSetObj;

  itk::ProgressAccumulator::Pointer const ProgressAccumulatorObj = itk::ProgressAccumulator::New();
  std::cout << "------------ProgressAccumulator" << ProgressAccumulatorObj;

  itk::QuaternionRigidTransform<double>::Pointer const QuaternionRigidTransformObj =
    itk::QuaternionRigidTransform<double>::New();
  std::cout << "------------QuaternionRigidTransform" << QuaternionRigidTransformObj;

  itk::RGBToVectorImageAdaptor<RGBImageType>::Pointer const RGBToVectorImageAdaptorObj =
    itk::RGBToVectorImageAdaptor<RGBImageType>::New();
  std::cout << "------------RGBToVectorImageAdaptor" << RGBToVectorImageAdaptorObj;

  itk::Rigid2DTransform<double>::Pointer const Rigid2DTransformObj = itk::Rigid2DTransform<double>::New();
  std::cout << "------------Rigid2DTransform" << Rigid2DTransformObj;

  itk::Rigid3DPerspectiveTransform<double>::Pointer const Rigid3DPerspectiveTransformObj =
    itk::Rigid3DPerspectiveTransform<double>::New();
  std::cout << "------------Rigid3DPerspectiveTransform" << Rigid3DPerspectiveTransformObj;

  itk::ScaleTransform<float, 3>::Pointer const ScaleTransformObj = itk::ScaleTransform<float, 3>::New();
  std::cout << "------------ScaleTransform" << ScaleTransformObj;

  itk::SegmentationBorder::Pointer const SegmentationBorderObj = itk::SegmentationBorder::New();
  std::cout << "------------SegmentationBorder" << SegmentationBorderObj;

  itk::SegmentationRegion::Pointer const SegmentationRegionObj = itk::SegmentationRegion::New();
  std::cout << "------------SegmentationRegion" << SegmentationRegionObj;

  itk::Similarity2DTransform<double>::Pointer const Similarity2DTransformObj =
    itk::Similarity2DTransform<double>::New();
  std::cout << "------------Similarity2DTransform" << Similarity2DTransformObj;

  itk::SinImageAdaptor<InputType, OutputType>::Pointer const SinImageAdaptorObj =
    itk::SinImageAdaptor<InputType, OutputType>::New();
  std::cout << "------------SinImageAdaptor" << SinImageAdaptorObj;

  itk::SphereSpatialFunction<2, PointType>::Pointer const SphereSpatialFunctionObj =
    itk::SphereSpatialFunction<2, PointType>::New();
  std::cout << "------------SphereSpatialFunction" << SphereSpatialFunctionObj;

  itk::SqrtImageAdaptor<InputType, OutputType>::Pointer const SqrtImageAdaptorObj =
    itk::SqrtImageAdaptor<InputType, OutputType>::New();
  std::cout << "------------SqrtImageAdaptor" << SqrtImageAdaptorObj;

  itk::SymmetricEllipsoidInteriorExteriorSpatialFunction<>::Pointer const
    SymmetricEllipsoidInteriorExteriorSpatialFunctionObj =
      itk::SymmetricEllipsoidInteriorExteriorSpatialFunction<>::New();
  std::cout << "------------SymmetricEllipsoidInteriorExteriorSpatialFunction"
            << SymmetricEllipsoidInteriorExteriorSpatialFunctionObj;

  itk::TanImageAdaptor<InputType, OutputType>::Pointer const TanImageAdaptorObj =
    itk::TanImageAdaptor<InputType, OutputType>::New();
  std::cout << "------------TanImageAdaptor" << TanImageAdaptorObj;

  itk::TextOutput::Pointer const TextOutputObj = itk::TextOutput::New();
  std::cout << "------------TextOutput" << TextOutputObj;

  itk::ThinPlateR2LogRSplineKernelTransform<double, 3>::Pointer const ThinPlateR2LogRSplineKernelTransformObj =
    itk::ThinPlateR2LogRSplineKernelTransform<double, 3>::New();
  std::cout << "------------ThinPlateR2LogRSplineKernelTransform" << ThinPlateR2LogRSplineKernelTransformObj;

  itk::ThinPlateSplineKernelTransform<double, 3>::Pointer const ThinPlateSplineKernelTransformObj =
    itk::ThinPlateSplineKernelTransform<double, 3>::New();
  std::cout << "------------ThinPlateSplineKernelTransform" << ThinPlateSplineKernelTransformObj;

  itk::TorusInteriorExteriorSpatialFunction<>::Pointer const TorusInteriorExteriorSpatialFunctionObj =
    itk::TorusInteriorExteriorSpatialFunction<>::New();
  std::cout << "------------TorusInteriorExteriorSpatialFunction" << TorusInteriorExteriorSpatialFunctionObj;

  itk::TranslationTransform<double, 3>::Pointer const TranslationTransformObj =
    itk::TranslationTransform<double, 3>::New();
  std::cout << "------------TranslationTransform" << TranslationTransformObj;

  itk::ValarrayImageContainer<unsigned long, PointType>::Pointer const ValarrayImageContainerObj =
    itk::ValarrayImageContainer<unsigned long, PointType>::New();
  std::cout << "------------ValarrayImageContainer" << ValarrayImageContainerObj;

  itk::VarianceImageFunction<InputType, float>::Pointer const VarianceImageFunctionObj =
    itk::VarianceImageFunction<InputType, float>::New();
  std::cout << "------------VarianceImageFunction" << VarianceImageFunctionObj;

  itk::VectorContainer<PointType>::Pointer const VectorContainerObj = itk::VectorContainer<PointType>::New();
  std::cout << "------------VectorContainer" << VectorContainerObj;

  itk::VectorImage<float, 3>::Pointer const VectorImageObj = itk::VectorImage<float, 3>::New();
  std::cout << "------------VectorImage" << VectorImageObj;

  itk::VectorLinearInterpolateImageFunction<VectorImageType, float>::Pointer const
    VectorLinearInterpolateImageFunctionObj = itk::VectorLinearInterpolateImageFunction<VectorImageType, float>::New();
  std::cout << "------------VectorLinearInterpolateImageFunction" << VectorLinearInterpolateImageFunctionObj;

  itk::VectorToRGBImageAdaptor<VectorImageType>::Pointer const VectorToRGBImageAdaptorObj =
    itk::VectorToRGBImageAdaptor<VectorImageType>::New();
  std::cout << "------------VectorToRGBImageAdaptor" << VectorToRGBImageAdaptorObj;

  itk::Version::Pointer const VersionObj = itk::Version::New();
  std::cout << "------------Version" << VersionObj;

  itk::ScaleSkewVersor3DTransform<double>::Pointer const ScaleSkewVersor3DTransformObj =
    itk::ScaleSkewVersor3DTransform<double>::New();
  std::cout << "------------ScaleSkewVersor3DTransform" << ScaleSkewVersor3DTransformObj;

  itk::VersorRigid3DTransform<double>::Pointer const VersorRigid3DTransformObj =
    itk::VersorRigid3DTransform<double>::New();
  std::cout << "------------VersorRigid3DTransform" << VersorRigid3DTransformObj;

  itk::VersorTransform<double>::Pointer const VersorTransformObj = itk::VersorTransform<double>::New();
  std::cout << "------------VersorTransform" << VersorTransformObj;

  itk::VolumeSplineKernelTransform<double, 3>::Pointer const VolumeSplineKernelTransformObj =
    itk::VolumeSplineKernelTransform<double, 3>::New();
  std::cout << "------------VolumeSplineKernelTransform" << VolumeSplineKernelTransformObj;

  itk::XMLFileOutputWindow::Pointer const XMLFileOutputWindowObj = itk::XMLFileOutputWindow::New();
  std::cout << "------------XMLFileOutputWindow" << XMLFileOutputWindowObj;


  return EXIT_SUCCESS;
}
