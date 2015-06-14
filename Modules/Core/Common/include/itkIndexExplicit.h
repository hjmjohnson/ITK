#ifndef itkIndexExplicit_H
#define itkIndexExplicit_H

extern template class ITKCommon_EXPORT itk::Index<2u>;
extern template class ITKCommon_EXPORT itk::Index<3u>;
extern template class ITKCommon_EXPORT itk::Index<4u>;
extern template class ITKCommon_EXPORT itk::Functor::IndexLexicographicCompare<2u>;
extern template class ITKCommon_EXPORT itk::Functor::IndexLexicographicCompare<3u>;
extern template class ITKCommon_EXPORT itk::Functor::IndexLexicographicCompare<4u>;

#endif // itkIndexExplicit_H
