#ifndef itkFiniteDifferenceFunctionExplicit_h
#define itkFiniteDifferenceFunctionExplicit_h
#include "itkImage.h"
#include "itkVector.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 57 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<itk::RGBPixel<float>, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<itk::CovariantVector<float, 2u>, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 66 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<double, 2u> >; //Instantiated 48 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<float, 3u> >; //Instantiated 90 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<itk::Vector<float, 3u>, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<double, 3u> >; //Instantiated 84 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<float, 2u> >; //Instantiated 204 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FiniteDifferenceFunction<itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 18 times
#endif //itkFiniteDifferenceFunctionExplicit_h
