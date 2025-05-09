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
#ifndef itkPointBasedSpatialObject_hxx
#define itkPointBasedSpatialObject_hxx


namespace itk
{

template <unsigned int TDimension, class TSpatialObjectPointType>
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::PointBasedSpatialObject()
  : SpatialObject<TDimension>()
{
  this->SetTypeName("PointBasedSpatialObject");

  this->Clear();

  this->Update();
}

template <unsigned int TDimension, class TSpatialObjectPointType>
void
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::Clear()
{
  Superclass::Clear();

  m_Points.clear();

  this->Modified();
}

template <unsigned int TDimension, class TSpatialObjectPointType>
void
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::AddPoint(const SpatialObjectPointType & newPoint)
{
  m_Points.push_back(newPoint);
  m_Points.back().SetSpatialObject(this);

  this->Modified();
}

template <unsigned int TDimension, class TSpatialObjectPointType>
void
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::RemovePoint(IdentifierType id)
{
  if (id < m_Points.size())
  {
    auto it = m_Points.begin();
    advance(it, id);
    m_Points.erase(it);
  }

  this->Modified();
}

template <unsigned int TDimension, class TSpatialObjectPointType>
void
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::SetPoints(const SpatialObjectPointListType & newPoints)
{
  m_Points.clear();

  auto it = newPoints.begin();
  while (it != newPoints.end())
  {
    m_Points.push_back(*it);
    m_Points.back().SetSpatialObject(this);
    ++it;
  }

  this->Modified();
}

template <unsigned int TDimension, class TSpatialObjectPointType>
TSpatialObjectPointType
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::ClosestPointInObjectSpace(const PointType & point) const
{
  auto it = m_Points.begin();
  auto itend = m_Points.end();

  if (it == itend)
  {
    itkExceptionMacro("SpatialObject: ClosestPoint called using an empty point list");
  }

  SpatialObjectPointType closestPoint;
  double                 closestPointDistance = NumericTraits<double>::max();
  while (it != itend)
  {
    const typename SpatialObjectPoint<TDimension>::PointType curpos = it->GetPositionInObjectSpace();
    const double                                             curdistance = curpos.EuclideanDistanceTo(point);
    if (curdistance < closestPointDistance)
    {
      closestPoint = (*it);
      closestPointDistance = curdistance;
    }
    ++it;
  }

  return closestPoint;
}

template <unsigned int TDimension, class TSpatialObjectPointType>
TSpatialObjectPointType
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::ClosestPointInWorldSpace(const PointType & point) const
{
  auto it = m_Points.begin();
  auto itend = m_Points.end();

  if (it == itend)
  {
    itkExceptionMacro("SpatialObject: ClosestPoint called using an empty point list");
  }

  SpatialObjectPointType closestPoint;
  double                 closestPointDistance = NumericTraits<double>::max();
  while (it != itend)
  {
    const typename SpatialObjectPoint<TDimension>::PointType curpos = it->GetPositionInWorldSpace();
    const double                                             curdistance = curpos.EuclideanDistanceTo(point);
    if (curdistance < closestPointDistance)
    {
      closestPoint = (*it);
      closestPointDistance = curdistance;
    }
    ++it;
  }

  return closestPoint;
}

template <unsigned int TDimension, class TSpatialObjectPointType>
void
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::ComputeMyBoundingBox()
{
  itkDebugMacro("Computing blob bounding box");

  auto it = m_Points.begin();
  auto end = m_Points.end();

  if (it == end)
  {
    const typename BoundingBoxType::PointType pnt{};
    this->GetModifiableMyBoundingBoxInObjectSpace()->SetMinimum(pnt);
    this->GetModifiableMyBoundingBoxInObjectSpace()->SetMaximum(pnt);
    return;
  }

  const PointType pt = it->GetPositionInObjectSpace();

  this->GetModifiableMyBoundingBoxInObjectSpace()->SetMinimum(pt);
  this->GetModifiableMyBoundingBoxInObjectSpace()->SetMaximum(pt);
  ++it;
  while (it != end)
  {
    this->GetModifiableMyBoundingBoxInObjectSpace()->ConsiderPoint(it->GetPositionInObjectSpace());
    ++it;
  }
  this->GetModifiableMyBoundingBoxInObjectSpace()->ComputeBoundingBox();
}

template <unsigned int TDimension, class TSpatialObjectPointType>
bool
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::IsInsideInObjectSpace(const PointType & point) const
{
  if (this->GetMyBoundingBoxInObjectSpace()->IsInside(point))
  {
    auto it = m_Points.begin();
    auto itEnd = m_Points.end();

    while (it != itEnd)
    {
      bool equals = true;
      for (unsigned int i = 0; i < TDimension; ++i)
      {
        if (!Math::AlmostEquals(point[i], it->GetPositionInObjectSpace()[i]))
        {
          equals = false;
          break;
        }
      }
      if (equals)
      {
        return true;
      }
      ++it;
    }
  }

  return false;
}

template <unsigned int TDimension, class TSpatialObjectPointType>
typename LightObject::Pointer
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::InternalClone() const
{
  // Default implementation just copies the parameters from
  // this to new transform.
  typename LightObject::Pointer loPtr = Superclass::InternalClone();

  const typename Self::Pointer rval = dynamic_cast<Self *>(loPtr.GetPointer());
  if (rval.IsNull())
  {
    itkExceptionMacro("downcast to type " << this->GetNameOfClass() << " failed.");
  }

  rval->SetPoints(this->GetPoints());

  return loPtr;
}

template <unsigned int TDimension, class TSpatialObjectPointType>
void
PointBasedSpatialObject<TDimension, TSpatialObjectPointType>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  // ToDo
  // os << indent << "Points: " << m_Points << std::endl;
}
} // end namespace itk

#endif // end itkPointBasedSpatialObject_hxx
