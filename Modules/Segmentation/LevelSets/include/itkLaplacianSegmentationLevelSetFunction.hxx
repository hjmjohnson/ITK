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
#ifndef itkLaplacianSegmentationLevelSetFunction_hxx
#define itkLaplacianSegmentationLevelSetFunction_hxx

#include "itkLaplacianImageFilter.h"
#include "itkCastImageFilter.h"

namespace itk
{
template <typename TImageType, typename TFeatureImageType>
void
LaplacianSegmentationLevelSetFunction<TImageType, TFeatureImageType>::CalculateSpeedImage()
{
  auto filter = LaplacianImageFilter<ImageType, ImageType>::New();

  auto caster = CastImageFilter<FeatureImageType, ImageType>::New();

  caster->SetInput(this->GetFeatureImage());
  filter->SetInput(caster->GetOutput());

  // make the laplacian filter use the pixel container from the speed image
  filter->GraftOutput(this->GetSpeedImage());

  filter->Update();

  // move the meta information (mostly the spacing and origin) back to
  // the speed image.
  //
  // unfortunately functions are not filters so we can't graft back
  this->GetSpeedImage()->Graft(filter->GetOutput());
}
} // end namespace itk

#endif
