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
#ifndef itkImageToImageFilterExplicit_h
#define itkImageToImageFilterExplicit_h
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<short, 2u>, itk::Image<short, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<int, 2u>, itk::Image<int, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<float, 2u>, itk::Image<float, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<double, 2u>, itk::Image<double, 2u> >;

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<short, 3u>, itk::Image<short, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<int, 3u>, itk::Image<int, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<float, 3u>, itk::Image<float, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToImageFilter< itk::Image<double, 3u>, itk::Image<double, 3u> >;
#endif //itkImageToImageFilterExplicit_h
