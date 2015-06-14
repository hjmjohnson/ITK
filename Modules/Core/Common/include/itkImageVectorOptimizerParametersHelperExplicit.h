/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkImageVectorOptimizerParametersHelperExplicit_h
#define itkImageVectorOptimizerParametersHelperExplicit_h
extern template class ITKCommon_EXPORT itk::ImageVectorOptimizerParametersHelper<float, 3u, 4u>;
extern template class ITKCommon_EXPORT itk::ImageVectorOptimizerParametersHelper<double, 2u, 3u>;
extern template class ITKCommon_EXPORT itk::ImageVectorOptimizerParametersHelper<double, 3u, 4u>;
extern template class ITKCommon_EXPORT itk::ImageVectorOptimizerParametersHelper<double, 4u, 4u>;
extern template class ITKCommon_EXPORT itk::ImageVectorOptimizerParametersHelper<float, 2u, 3u>;
extern template class ITKCommon_EXPORT itk::ImageVectorOptimizerParametersHelper<float, 3u, 3u>;
extern template class ITKCommon_EXPORT itk::ImageVectorOptimizerParametersHelper<double, 3u, 3u>;
extern template class ITKCommon_EXPORT itk::ImageVectorOptimizerParametersHelper<double, 2u, 2u>;
extern template class ITKCommon_EXPORT itk::ImageVectorOptimizerParametersHelper<float, 2u, 2u>;
#endif //itkImageVectorOptimizerParametersHelperExplicit_h
