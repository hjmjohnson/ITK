#ifndef itkMeshExplicit_h
#define itkMeshExplicit_h

#include "ITKMeshExport.h"

#include "itkSymmetricSecondRankTensor.h"
#include "itkVariableLengthVector.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<itk::VariableLengthVector<float>, 3u, itk::DefaultStaticMeshTraits<itk::VariableLengthVector<float>, 3u, 3u, float, float, itk::VariableLengthVector<float> > >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<itk::CovariantVector<float, 3u>, 3u, itk::DefaultStaticMeshTraits<itk::CovariantVector<float, 3u>, 3u, 3u, float, float, itk::CovariantVector<float, 3u> > >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<double, 2u, itk::DefaultDynamicMeshTraits<double, 2u, 2u, double, float, double> >; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<float, 2u, itk::DefaultStaticMeshTraits<float, 2u, 2u, float, float, float> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<int, 3u, itk::DefaultStaticMeshTraits<int, 3u, 3u, float, float, int> >; //Instantiated 24 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> >; //Instantiated 21 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<unsigned short, 3u, itk::DefaultStaticMeshTraits<unsigned short, 3u, 3u, float, float, unsigned short> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<itk::Point<float, 2u>, 3u, itk::DefaultStaticMeshTraits<itk::Point<float, 2u>, 3u, 3u, float, float, itk::Point<float, 2u> > >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, float, float, double> >; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<float, 3u, itk::DefaultDynamicMeshTraits<float, 3u, 3u, float, float, float> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<unsigned char, 2u, itk::DefaultStaticMeshTraits<unsigned char, 2u, 2u, float, float, unsigned char> >; //Instantiated 54 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<unsigned char, 3u, itk::DefaultStaticMeshTraits<unsigned char, 3u, 3u, float, float, unsigned char> >; //Instantiated 24 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, float, float, double> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::Mesh<float, 3u, itk::DefaultStaticMeshTraits<float, 3u, 3u, float, float, float> >; //Instantiated 51 times
#endif //itkMeshExplicit_h
