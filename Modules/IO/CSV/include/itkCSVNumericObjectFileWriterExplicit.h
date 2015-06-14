#ifndef itkCSVNumericObjectFileWriterExplicit_h
#define itkCSVNumericObjectFileWriterExplicit_h

#include "ITKIOCSVExport.h"

extern template class ITKIOCSV_EXPORT itk::CSVNumericObjectFileWriter<double, 3u, 4u>; //Instantiated 3 times
extern template class ITKIOCSV_EXPORT itk::CSVNumericObjectFileWriter<double, 3u, 6u>; //Instantiated 6 times
extern template class ITKIOCSV_EXPORT itk::CSVNumericObjectFileWriter<double, 3u, 3u>; //Instantiated 3 times
#endif //itkCSVNumericObjectFileWriterExplicit_h
