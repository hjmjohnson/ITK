#ifndef VNL_EXPLICIT_H
#define VNL_EXPLICIT_H

#include "vnl/vnl_matrix.h"
#include "vnl/vnl_vector.h"

extern template class ITKCommon_EXPORT vnl_matrix<double>;
extern template class ITKCommon_EXPORT vnl_matrix<unsigned long>;
extern template class ITKCommon_EXPORT vnl_matrix<unsigned int>;
extern template class ITKCommon_EXPORT vnl_matrix<float>;

extern template class ITKCommon_EXPORT vnl_vector<double>;
extern template class ITKCommon_EXPORT vnl_vector<unsigned long>;
extern template class ITKCommon_EXPORT vnl_vector<unsigned int>;
extern template class ITKCommon_EXPORT vnl_vector<float>;

#endif //VNL_EXPLICIT_H
