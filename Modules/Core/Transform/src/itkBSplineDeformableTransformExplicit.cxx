#include "itkBSplineDeformableTransform.h"

template class itk::BSplineDeformableTransform<float, 3u, 3u>; //Instantiated 6 times
template class itk::BSplineDeformableTransform<double, 3u, 3u>; //Instantiated 12 times
template class itk::BSplineDeformableTransform<double, 2u, 2u>; //Instantiated 6 times
template class itk::BSplineDeformableTransform<double, 2u, 3u>; //Instantiated 9 times
