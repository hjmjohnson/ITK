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

#ifndef itkWhitakerSparseLevelSetImage_h
#define itkWhitakerSparseLevelSetImage_h

#include "itkLevelSetSparseImage.h"
#include "itkLabelObject.h"
#include "itkLabelMap.h"

namespace itk
{
/**
 *  \class WhitakerSparseLevelSetImage
 *  \brief Derived class for the sparse-field representation of level-set function
 *
 *  This representation is a "sparse" level-set function, where values are
 *  real in between [ -3, +3 ] and organized into several layers { -2, -1,
 *  0, +1, +2 }.
 *
 *  \tparam TOutput Output type (float or double) of the level set function
 *  \tparam VDimension Dimension of the input space
 *  \ingroup ITKLevelSetsv4
 */
template <typename TOutput, unsigned int VDimension>
class ITK_TEMPLATE_EXPORT WhitakerSparseLevelSetImage : public LevelSetSparseImage<TOutput, VDimension>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(WhitakerSparseLevelSetImage);

  using Self = WhitakerSparseLevelSetImage;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;
  using Superclass = LevelSetSparseImage<TOutput, VDimension>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(WhitakerSparseLevelSetImage);

  static constexpr unsigned int Dimension = VDimension;

  using typename Superclass::InputType;
  using typename Superclass::OutputType;
  using typename Superclass::OutputRealType;
  using typename Superclass::GradientType;
  using typename Superclass::HessianType;
  using typename Superclass::LevelSetDataType;

  using typename Superclass::LayerIdType;
  using typename Superclass::LabelObjectType;
  using typename Superclass::LabelObjectPointer;
  using typename Superclass::LabelObjectLengthType;
  using typename Superclass::LabelObjectLineType;

  using typename Superclass::LabelMapType;
  using typename Superclass::LabelMapPointer;
  using typename Superclass::LabelMapConstPointer;
  using typename Superclass::RegionType;

  using typename Superclass::LayerType;
  using typename Superclass::LayerIterator;
  using typename Superclass::LayerConstIterator;

  using typename Superclass::LayerMapType;
  using typename Superclass::LayerMapIterator;
  using typename Superclass::LayerMapConstIterator;

  /** Returns the value of the level set function at a given location iP */
  using Superclass::Evaluate;
  OutputType
  Evaluate(const InputType & inputIndex) const override;

  itkConceptMacro(DoubleConvertible, (Concept::Convertible<OutputRealType, OutputType>));

  static inline LayerIdType
  MinusThreeLayer()
  {
    return -3;
  }
  static inline LayerIdType
  MinusTwoLayer()
  {
    return -2;
  }
  static inline LayerIdType
  MinusOneLayer()
  {
    return -1;
  }
  static inline LayerIdType
  ZeroLayer()
  {
    return 0;
  }
  static inline LayerIdType
  PlusOneLayer()
  {
    return 1;
  }
  static inline LayerIdType
  PlusTwoLayer()
  {
    return 2;
  }
  static inline LayerIdType
  PlusThreeLayer()
  {
    return 3;
  }

  /** Return the label object pointer with a given id */
  template <typename TLabel>
  typename LabelObject<TLabel, Dimension>::Pointer
  GetAsLabelObject()
  {
    using OutputLabelObjectType = LabelObject<TLabel, Dimension>;
    auto object = OutputLabelObjectType::New();

    for (LayerIdType status = this->MinusThreeLayer(); status < this->PlusOneLayer(); ++status)
    {
      const LabelObjectPointer labelObject = this->m_LabelMap->GetLabelObject(status);

      for (SizeValueType i = 0; i < labelObject->GetNumberOfLines(); ++i)
      {
        object->AddLine(labelObject->GetLine(i));
      }
    }
    object->Optimize();

    return object;
  }

protected:
  WhitakerSparseLevelSetImage();
  ~WhitakerSparseLevelSetImage() override = default;

  /** Initialize the sparse field layers */
  void
  InitializeLayers() override;

  void
  InitializeInternalLabelList() override;
};
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkWhitakerSparseLevelSetImage.hxx"
#endif

#endif // itkWhitakerSparseLevelSetImage_h
