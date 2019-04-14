#include "itkDisplacementFieldJacobianDeterminantFilter.h"

template class itk::DisplacementFieldJacobianDeterminantFilter<itk::Image<itk::Vector<float, 2u>, 2u>, float, itk::Image<float, 2u> >; //Instantiated 6 times
template class itk::DisplacementFieldJacobianDeterminantFilter<itk::Image<itk::Vector<float, 3u>, 3u>, float, itk::Image<float, 3u> >; //Instantiated 53 times
