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

#include "itkMRIBiasFieldCorrectionFilter.h"
#include "itkShapeDetectionLevelSetImageFilter.h"
#include "itkSphereMeshSource.h"
#include "itkThresholdSegmentationLevelSetImageFilter.h"
#include "itkVoronoiPartitioningImageFilter.h"
#include "itkVoronoiSegmentationImageFilter.h"
#include "itkVoronoiSegmentationRGBImageFilter.h"
#include "itkWatershedBoundaryResolver.h"
#include "itkWatershedEquivalenceRelabeler.h"
#include "itkWatershedImageFilter.h"

int
main(int, char *[])
{
  using InputType = itk::Image<float, 2>;
  using OutputType = itk::Image<float, 2>;

  using CharType = itk::Image<unsigned char, 2>;

  using MeshType = itk::Mesh<double>;

  using RGBVectorType = itk::Vector<float, 3>;
  using RGBVectorImageType = itk::Image<RGBVectorType, 2>;

  itk::ShapeDetectionLevelSetFunction<InputType, InputType>::Pointer const ShapeDetectionLevelSetFunctionObj =
    itk::ShapeDetectionLevelSetFunction<InputType, InputType>::New();
  std::cout << "-------------ShapeDetectionLevelSetFunction " << ShapeDetectionLevelSetFunctionObj;

  itk::ShapeDetectionLevelSetImageFilter<InputType, InputType, float>::Pointer const
    ShapeDetectionLevelSetImageFilterObj = itk::ShapeDetectionLevelSetImageFilter<InputType, InputType, float>::New();
  std::cout << "-------------ShapeDetectionLevelSetImageFilter " << ShapeDetectionLevelSetImageFilterObj;

  itk::SphereMeshSource<MeshType>::Pointer const SphereMeshSourceObj = itk::SphereMeshSource<MeshType>::New();
  std::cout << "-------------SphereMeshSource " << SphereMeshSourceObj;

  itk::ThresholdSegmentationLevelSetFunction<InputType, InputType>::Pointer const
    ThresholdSegmentationLevelSetFunctionObj = itk::ThresholdSegmentationLevelSetFunction<InputType, InputType>::New();
  std::cout << "-------------ThresholdSegmentationLevelSetFunction " << ThresholdSegmentationLevelSetFunctionObj;

  itk::ThresholdSegmentationLevelSetImageFilter<InputType, InputType, float>::Pointer const
    ThresholdSegmentationLevelSetImageFilterObj =
      itk::ThresholdSegmentationLevelSetImageFilter<InputType, InputType, float>::New();
  std::cout << "-------------ThresholdSegmentationLevelSetImageFilter " << ThresholdSegmentationLevelSetImageFilterObj;

  itk::VoronoiDiagram2D<double>::Pointer const VoronoiDiagram2DObj = itk::VoronoiDiagram2D<double>::New();
  std::cout << "-------------VoronoiDiagram2D " << VoronoiDiagram2DObj;

  itk::VoronoiDiagram2DGenerator<double>::Pointer const VoronoiDiagram2DGeneratorObj =
    itk::VoronoiDiagram2DGenerator<double>::New();
  std::cout << "-------------VoronoiDiagram2DGenerator " << VoronoiDiagram2DGeneratorObj;

  itk::VoronoiPartitioningImageFilter<InputType, OutputType>::Pointer const VoronoiPartitioningImageFilterObj =
    itk::VoronoiPartitioningImageFilter<InputType, OutputType>::New();
  std::cout << "-------------VoronoiPartitioningImageFilter " << VoronoiPartitioningImageFilterObj;

  itk::VoronoiSegmentationImageFilter<InputType, OutputType>::Pointer const VoronoiSegmentationImageFilterObj =
    itk::VoronoiSegmentationImageFilter<InputType, OutputType>::New();
  std::cout << "-------------VoronoiSegmentationImageFilter " << VoronoiSegmentationImageFilterObj;

  itk::VoronoiSegmentationImageFilterBase<InputType, OutputType>::Pointer const VoronoiSegmentationImageFilterBaseObj =
    itk::VoronoiSegmentationImageFilterBase<InputType, OutputType>::New();
  std::cout << "-------------VoronoiSegmentationImageFilterBase " << VoronoiSegmentationImageFilterBaseObj;

  itk::VoronoiSegmentationRGBImageFilter<RGBVectorImageType, CharType>::Pointer const
    VoronoiSegmentationRGBImageFilterObj = itk::VoronoiSegmentationRGBImageFilter<RGBVectorImageType, CharType>::New();
  std::cout << "-------------VoronoiSegmentationRGBImageFilter " << VoronoiSegmentationRGBImageFilterObj;

  itk::watershed::Boundary<double, 3>::Pointer const WatershedBoundaryObj = itk::watershed::Boundary<double, 3>::New();
  std::cout << "-------------WatershedBoundary " << WatershedBoundaryObj;

  itk::watershed::BoundaryResolver<double, 3>::Pointer const WatershedBoundaryResolverObj =
    itk::watershed::BoundaryResolver<double, 3>::New();
  std::cout << "-------------WatershedBoundaryResolver " << WatershedBoundaryResolverObj;

  itk::watershed::EquivalenceRelabeler<double, 3>::Pointer const WatershedEquivalenceRelabelerObj =
    itk::watershed::EquivalenceRelabeler<double, 3>::New();
  std::cout << "-------------WatershedEquivalenceRelabeler " << WatershedEquivalenceRelabelerObj;

  itk::WatershedImageFilter<InputType>::Pointer const WatershedImageFilterObj =
    itk::WatershedImageFilter<InputType>::New();
  std::cout << "-------------WatershedImageFilter " << WatershedImageFilterObj;

  itk::WatershedMiniPipelineProgressCommand::Pointer const WatershedMiniPipelineProgressCommandObj =
    itk::WatershedMiniPipelineProgressCommand::New();
  std::cout << "-------------WatershedMiniPipelineProgressCommand " << WatershedMiniPipelineProgressCommandObj;

  itk::watershed::Relabeler<double, 3>::Pointer const WatershedRelabelerObj =
    itk::watershed::Relabeler<double, 3>::New();
  std::cout << "-------------WatershedRelabeler " << WatershedRelabelerObj;

  itk::watershed::SegmentTable<double>::Pointer const WatershedSegmentTableObj =
    itk::watershed::SegmentTable<double>::New();
  std::cout << "-------------WatershedSegmentTable " << WatershedSegmentTableObj;

  itk::watershed::SegmentTree<double>::Pointer const WatershedSegmentTreeObj =
    itk::watershed::SegmentTree<double>::New();
  std::cout << "-------------WatershedSegmentTree " << WatershedSegmentTreeObj;

  itk::watershed::SegmentTreeGenerator<double>::Pointer const WatershedSegmentTreeGeneratorObj =
    itk::watershed::SegmentTreeGenerator<double>::New();
  std::cout << "-------------WatershedSegmentTreeGenerator " << WatershedSegmentTreeGeneratorObj;

  itk::watershed::Segmenter<InputType>::Pointer const WatershedSegmenterObj =
    itk::watershed::Segmenter<InputType>::New();
  std::cout << "-------------WatershedSegmenter " << WatershedSegmenterObj;

  itk::MRASlabIdentifier<InputType>::Pointer const MRASlabIdentifierObj = itk::MRASlabIdentifier<InputType>::New();
  std::cout << "-------------MRASlabIdentifier " << MRASlabIdentifierObj;
  return EXIT_SUCCESS;
}
