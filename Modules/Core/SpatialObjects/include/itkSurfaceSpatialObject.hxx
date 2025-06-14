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
#ifndef itkSurfaceSpatialObject_hxx
#define itkSurfaceSpatialObject_hxx


#include "itkMath.h"

namespace itk
{

template <unsigned int TDimension, typename TSurfacePointType>
SurfaceSpatialObject<TDimension, TSurfacePointType>::SurfaceSpatialObject()
{
  this->SetTypeName("SurfaceSpatialObject");

  this->Clear();

  this->Update();
}

template <unsigned int TDimension, typename TSurfacePointType>
void
SurfaceSpatialObject<TDimension, TSurfacePointType>::Clear()
{
  Superclass::Clear();

  this->GetProperty().SetRed(1);
  this->GetProperty().SetGreen(0);
  this->GetProperty().SetBlue(0);
  this->GetProperty().SetAlpha(1);

  this->Modified();
}

template <unsigned int TDimension, typename TSurfacePointType>
typename LightObject::Pointer
SurfaceSpatialObject<TDimension, TSurfacePointType>::InternalClone() const
{
  // Default implementation just copies the parameters from
  // this to new transform.
  typename LightObject::Pointer loPtr = Superclass::InternalClone();

  const typename Self::Pointer rval = dynamic_cast<Self *>(loPtr.GetPointer());
  if (rval.IsNull())
  {
    itkExceptionMacro("downcast to type " << this->GetNameOfClass() << " failed.");
  }

  return loPtr;
}

#if !defined(ITK_LEGACY_REMOVE)
template <unsigned int TDimension, typename TSurfacePointType>
bool
SurfaceSpatialObject<TDimension, TSurfacePointType>::Approximate3DNormals()
{
  return ComputeNormals;
}
#endif // LEGACY

template <unsigned int TDimension, typename TSurfacePointType>
bool
SurfaceSpatialObject<TDimension, TSurfacePointType>::ComputeNormals()
{
  if (this->m_Points.size() < 3)
  {
    itkExceptionMacro("ComputeNormals requires at least 3 points");
  }

  typename SurfacePointListType::iterator       it = this->m_Points.begin();
  const typename SurfacePointListType::iterator itEnd = this->m_Points.end();

  while (it != itEnd)
  {
    // Try to find 3 points close to the corresponding point
    const SurfacePointType pt = *it;
    const PointType        pos = it->GetPositionInObjectSpace();

    std::list<int> badId;
    unsigned int   identifier[3];
    double         absvec = 0;
    do
    {
      identifier[0] = 0;
      identifier[1] = 0;
      identifier[2] = 0;

      float max[3];
      max[0] = 99999999;
      max[1] = 99999999;
      max[2] = 99999999;

      typename SurfacePointListType::const_iterator it2 = this->m_Points.begin();

      int i = 0;
      while (it2 != this->m_Points.end())
      {
        if (it2 == it)
        {
          ++i;
          ++it2;
          continue;
        }

        bool badPoint = false;
        auto itBadId = badId.begin();
        while (itBadId != badId.end())
        {
          if (*itBadId == i)
          {
            badPoint = true;
            break;
          }
          ++itBadId;
        }

        if (badPoint)
        {
          ++i;
          ++it2;
          continue;
        }

        const PointType pos2 = it2->GetPositionInObjectSpace();
        const float     distance = pos2.EuclideanDistanceTo(pos);

        // Check that the point is not the same as some previously defined
        bool valid = true;
        for (auto & j : identifier)
        {
          const PointType p = this->m_Points[j].GetPositionInObjectSpace();
          const float     d = pos2.EuclideanDistanceTo(p);
          if (Math::AlmostEquals(d, 0.0f))
          {
            valid = false;
            break;
          }
        }

        if (Math::AlmostEquals(distance, 0.0f) || !valid)
        {
          ++i;
          ++it2;
          continue;
        }

        if (distance < max[0])
        {
          max[2] = max[1];
          max[1] = max[0];
          max[0] = distance;
          identifier[0] = i;
        }
        else if (distance < max[1])
        {
          max[2] = max[1];
          max[1] = distance;
          identifier[1] = i;
        }
        else if (distance < max[2])
        {
          max[2] = distance;
          identifier[2] = i;
        }
        ++i;
        ++it2;
      }

      if ((identifier[0] == identifier[1]) || (identifier[1] == identifier[2]) || (identifier[0] == identifier[2]))
      {
        std::cout << "Cannot find 3 distinct points!" << std::endl
                  << identifier[0] << " : " << identifier[1] << " : " << identifier[2] << std::endl
                  << max[0] << " : " << max[1] << " : " << max[2] << std::endl;
        return false;
      }

      PointType v1 = this->m_Points[identifier[0]].GetPositionInObjectSpace();
      PointType v2 = this->m_Points[identifier[1]].GetPositionInObjectSpace();
      PointType v3 = this->m_Points[identifier[2]].GetPositionInObjectSpace();

      if constexpr (TDimension == 3)
      {
        const double coa = -(v1[1] * (v2[2] - v3[2]) + v2[1] * (v3[2] - v1[2]) + v3[1] * (v1[2] - v2[2]));
        const double cob = -(v1[2] * (v2[0] - v3[0]) + v2[2] * (v3[0] - v1[0]) + v3[2] * (v1[0] - v2[0]));
        const double coc = -(v1[0] * (v2[1] - v3[1]) + v2[0] * (v3[1] - v1[1]) + v3[0] * (v1[1] - v2[1]));

        absvec = -std::sqrt(((coa * coa) + (cob * cob) + (coc * coc)));

        if (Math::AlmostEquals(absvec, 0.0))
        {
          badId.push_back(identifier[2]);
        }
        else
        {
          CovariantVectorType normal;
          normal[0] = coa / absvec;
          normal[1] = cob / absvec;
          normal[2] = coc / absvec;
          it->SetNormalInObjectSpace(normal);
        }
      }
      else
      {
        const double coa = -(v1[1] * (v2[0] - v3[0]) + v2[1] * (v3[0] - v1[0]) + v3[1] * (v1[0] - v2[0]));
        const double cob = -(v1[0] * (v2[1] - v3[1]) + v2[0] * (v3[1] - v1[1]) + v3[0] * (v1[1] - v2[1]));

        absvec = -std::sqrt(((coa * coa) + (cob * cob)));

        if (Math::AlmostEquals(absvec, 0.0))
        {
          badId.push_back(identifier[2]);
        }
        else
        {
          CovariantVectorType normal;
          normal[0] = coa / absvec;
          normal[1] = cob / absvec;
          it->SetNormalInObjectSpace(normal);
        }
      }
    } while ((Math::AlmostEquals(absvec, 0.0)) && (badId.size() < this->m_Points.size() - 1));

    if (Math::AlmostEquals(absvec, 0.0))
    {
      std::cout << "ComputeNormals Failed!" << std::endl
                << identifier[0] << " : " << identifier[1] << " : " << identifier[2] << std::endl
                << badId.size() << " : " << this->m_Points.size() - 1 << std::endl;
      return false;
    }

    ++it;
  }

  return true;
}

} // end namespace itk

#endif
