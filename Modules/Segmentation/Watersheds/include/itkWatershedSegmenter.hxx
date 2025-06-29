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
#ifndef itkWatershedSegmenter_hxx
#define itkWatershedSegmenter_hxx

#include "itkMath.h"
#include "itkNeighborhoodAlgorithm.h"
#include "itkImageRegionIterator.h"
#include <stack>
#include <list>

namespace itk::watershed
{

/*
  ----------------------------------------------------------------------------
  Algorithm methods
  ----------------------------------------------------------------------------
*/

template <typename TInputImage>
Segmenter<TInputImage>::~Segmenter()
{
  delete[] m_Connectivity.index;
  delete[] m_Connectivity.direction;
}

template <typename TInputImage>
void
Segmenter<TInputImage>::GenerateData()
{
  //
  // Allocate all the necessary temporary data structures and variables that
  // will be used in this algorithm.  Also re-initialize some temporary data
  // structures that may have been used in previous updates of this filter.
  //
  this->UpdateProgress(0.0);
  if (m_DoBoundaryAnalysis == false)
  {
    this->GetSegmentTable()->Clear();
    this->SetCurrentLabel(1);
  }

  const typename InputImageType::Pointer  input = this->GetInputImage();
  const typename OutputImageType::Pointer output = this->GetOutputImage();
  const typename BoundaryType::Pointer    boundary = this->GetBoundary();

  // ------------------------------------------------------------------------
  //
  // HERE ARE THE ASSUMPTIONS ABOUT REGION SIZES FOR NOW.  WHEN THE PIPELINE
  // FULLY SUPPORTS STREAMING, THESE WILL NEED TO BE CHANGED ACCORDINGLY.
  //
  // 1) All region sizes are equivalent.  There is no distinction among
  // regions.  The region size is assumed to be padded one pixel out along each
  // chunk face unless that face touches an actual data set boundary.
  //
  // 2) The ivar m_LargestPossibleRegion represents the actual size of the data
  // set.  This has to be set by the user since the pipeline sometimes clobbers
  // the actual LargestPossibleRegion (?).
  //
  // -------------------------------------------------------------------------

  //
  // Generate the "face" regions A that constitute our shared boundary with
  // another chunk.  Also determine which face regions B lie on a the true
  // dataset boundary.  The faces corresponding to B will need to be padded
  // out a pixel when we threshold so that we can construct the retaining wall
  // along those faces.
  //
  ImageRegionType       regionToProcess = output->GetRequestedRegion();
  const ImageRegionType largestPossibleRegion = this->GetLargestPossibleRegion();
  ImageRegionType       thresholdImageRegion = regionToProcess;
  ImageRegionType       thresholdLargestPossibleRegion = this->GetLargestPossibleRegion();

  // First we have to find the boundaries and adjust the threshold image size
  typename ImageRegionType::IndexType tidx = thresholdImageRegion.GetIndex();
  typename ImageRegionType::SizeType  tsz = thresholdImageRegion.GetSize();
  typename ImageRegionType::IndexType tlidx = thresholdLargestPossibleRegion.GetIndex();
  typename ImageRegionType::SizeType  tlsz = thresholdLargestPossibleRegion.GetSize();
  for (unsigned int i = 0; i < ImageDimension; ++i)
  {

    typename ImageRegionType::IndexType idx = regionToProcess.GetIndex();
    typename ImageRegionType::SizeType  sz = regionToProcess.GetSize();

    // Set LOW face
    idx[i] = regionToProcess.GetIndex()[i];
    sz[i] = 1;
    ImageRegionType reg;
    reg.SetSize(sz);
    reg.SetIndex(idx);

    if (reg.GetIndex()[i] == largestPossibleRegion.GetIndex()[i])
    {
      // This is facing a true data set boundary
      tsz[i] += 1; // we need to pad our threshold image on this face
      tidx[i] -= 1;
      tlsz[i] += 1; // we need to pad our threshold image on this face
      tlidx[i] -= 1;

      boundary->SetValid(false, i, 0);
    }
    else
    {
      // This is an overlap with another data chunk in the data set
      // Mark this boundary face as valid.
      boundary->SetValid(true, i, 0);
    }

    // Set HIGH face
    idx[i] = (regionToProcess.GetIndex()[i] + regionToProcess.GetSize()[i]) - 1;
    reg.SetSize(sz);
    reg.SetIndex(idx);
    if ((reg.GetIndex()[i] + reg.GetSize()[i]) ==
        (largestPossibleRegion.GetIndex()[i] + largestPossibleRegion.GetSize()[i]))
    {
      // This is facing a true data set boundary
      tsz[i] += 1;  // we need to pad our threshold image on this face
      tlsz[i] += 1; // we need to pad our threshold image on this face
      boundary->SetValid(false, i, 1);
    }
    else
    {
      // This is an overlap with another data chunk in the data set
      // Mark this face as valid in the boundary.
      boundary->SetValid(true, i, 1);
    }
  }
  thresholdImageRegion.SetSize(tsz);
  thresholdImageRegion.SetIndex(tidx);
  thresholdLargestPossibleRegion.SetSize(tlsz);
  thresholdLargestPossibleRegion.SetIndex(tlidx);

  // Now create and allocate the threshold image.  We need a single pixel
  // border around the NxM region we are segmenting.  This means that for faces
  // that have no overlap into another chunk, we have to pad the image.
  auto thresholdImage = InputImageType::New();

  thresholdImage->SetLargestPossibleRegion(thresholdLargestPossibleRegion);
  thresholdImage->SetBufferedRegion(thresholdImageRegion);
  thresholdImage->SetRequestedRegion(thresholdImageRegion);
  thresholdImage->Allocate();

  // Now threshold the image. First we calculate the dynamic range of
  // the input.  Then, the threshold operation clamps the lower
  // intensity values at the prescribed threshold.  If the data is
  // integral, then any intensity at NumericTraits<>::max() is reduced
  // by one intensity value.  This allows the watershed algorithm to
  // build a barrier around the image with values above the maximum
  // intensity value which trivially stop the steepest descent search
  // for local minima without requiring expensive boundary conditions.
  //
  //
  InputPixelType minimum;
  InputPixelType maximum;
  Self::MinMax(input, regionToProcess, minimum, maximum);
  // cap the maximum in the image so that we can always define a pixel
  // value that is one greater than the maximum value in the image.
  ITK_GCC_PRAGMA_PUSH
  ITK_GCC_SUPPRESS_Wfloat_equal
  if (std::is_integral_v<InputPixelType> && maximum == NumericTraits<InputPixelType>::max())
  {
    maximum -= NumericTraits<InputPixelType>::OneValue();
  }
  ITK_GCC_PRAGMA_POP
  // threshold the image.
  Self::Threshold(thresholdImage,
                  input,
                  regionToProcess,
                  regionToProcess,
                  static_cast<InputPixelType>((m_Threshold * (maximum - minimum)) + minimum));

  //
  // Redefine the regionToProcess in terms of the threshold image.  The region
  // to  process represents all the pixels contained within the 1 pixel padded
  // boundary of the threshold image.
  //
  typename ImageRegionType::SizeType  irsz;
  typename ImageRegionType::IndexType iridx;
  for (unsigned int i = 0; i < ImageDimension; ++i)
  {
    irsz[i] = thresholdImageRegion.GetSize()[i] - 2;
    iridx[i] = thresholdImageRegion.GetIndex()[i] + 1;
  }
  regionToProcess.SetIndex(iridx);
  regionToProcess.SetSize(irsz);

  //
  // Initialize the connectivity information that will be used by the
  // segmentation algorithm.
  //
  this->GenerateConnectivity();

  //
  // Store the regionToProcess in the RequestedRegion of the threshold image.
  // We are now completely done with the input image.  The input image memory
  // can be released at this point if need be.
  //
  thresholdImage->SetRequestedRegion(regionToProcess);
  this->ReleaseInputs();

  //
  // At this point we are ready to define the output
  // buffer and allocate memory for the output image.
  //
  output->SetBufferedRegion(thresholdImage->GetBufferedRegion());
  output->Allocate();
  Self::SetOutputImageValues(output, output->GetBufferedRegion(), Self::NULL_LABEL);

  //
  // Now we can create appropriate boundary regions for analyzing the
  // flow at the boundaries from the requested region of the threshold
  // image.
  //
  typename BoundaryType::IndexType    b_idx;
  ImageRegionType                     reg_b;
  typename ImageRegionType::IndexType idx_b;
  typename ImageRegionType::SizeType  sz_b;

  for (b_idx.first = 0; b_idx.first < ImageDimension; ++b_idx.first)
  {
    for (b_idx.second = 0; b_idx.second < 2; ++b_idx.second)
    {
      if (boundary->GetValid(b_idx) == false)
      {
        continue;
      }
      idx_b = thresholdImage->GetRequestedRegion().GetIndex();
      sz_b = thresholdImage->GetRequestedRegion().GetSize();

      if (b_idx.second == 1) // HIGH face must adjust start index
      {
        idx_b[b_idx.first] += sz_b[b_idx.first] - 1;
      }

      sz_b[b_idx.first] = 1;

      reg_b.SetIndex(idx_b);
      reg_b.SetSize(sz_b);

      boundary->GetFace(b_idx)->SetRegions(reg_b);
      boundary->GetFace(b_idx)->Allocate();
    }
  }
  this->UpdateProgress(0.1);

  //
  // Analyze the flow at the boundaries.  This method labels all the boundary
  // pixels that flow out of this chunk (either through gradient descent or
  // flat-region connectivity) and constructs the appropriate Boundary
  // data structures.
  //
  flat_region_table_t flatRegions;
  if (m_DoBoundaryAnalysis)
  {
    this->InitializeBoundary();
    this->AnalyzeBoundaryFlow(thresholdImage, flatRegions, maximum + NumericTraits<InputPixelType>::OneValue());
  }

  this->UpdateProgress(0.2);

  //
  // Build a "retaining wall" around the image so that gradient descent
  // analysis can be done without worrying about boundaries.
  //
  // All overlap boundary information will be overwritten, but is no longer
  // needed now.
  //
  this->BuildRetainingWall(
    thresholdImage, thresholdImage->GetBufferedRegion(), maximum + NumericTraits<InputPixelType>::OneValue());


  //
  // Label all the local minima pixels in the image.  This function also
  // labels flat regions, defined as regions where connected pixels all have
  // the same value.
  //
  this->LabelMinima(thresholdImage,
                    thresholdImage->GetRequestedRegion(),
                    flatRegions,
                    maximum + NumericTraits<InputPixelType>::OneValue());
  this->UpdateProgress(0.3);

  this->GradientDescent(thresholdImage, thresholdImage->GetRequestedRegion());
  this->UpdateProgress(0.4);

  this->DescendFlatRegions(flatRegions, thresholdImage->GetRequestedRegion());
  this->UpdateProgress(0.5);

  this->UpdateSegmentTable(thresholdImage, thresholdImage->GetRequestedRegion());
  this->UpdateProgress(0.6);

  if (m_DoBoundaryAnalysis)
  {
    this->CollectBoundaryInformation(flatRegions);
  }
  this->UpdateProgress(0.7);

  if (m_SortEdgeLists)
  {
    this->GetSegmentTable()->SortEdgeLists();
  }
  this->UpdateProgress(0.8);

  this->GetSegmentTable()->SetMaximumDepth(maximum - minimum);
  this->UpdateProgress(1.0);
}

template <typename TInputImage>
void
Segmenter<TInputImage>::CollectBoundaryInformation(flat_region_table_t & flatRegions)
{
  const typename OutputImageType::Pointer output = this->GetOutputImage();
  const typename BoundaryType::Pointer    boundary = this->GetBoundary();

  typename BoundaryType::IndexType idx;
  for (idx.first = 0; idx.first < ImageDimension; (idx.first)++)
  {
    for (idx.second = 0; idx.second < 2; (idx.second)++)
    {
      if (boundary->GetValid(idx) == false)
      {
        continue;
      }

      const typename BoundaryType::face_t::Pointer face = boundary->GetFace(idx);
      typename BoundaryType::flat_hash_t *         flats = boundary->GetFlatHash(idx);
      const ImageRegionType                        region = face->GetRequestedRegion();

      // Grab all the labels of the boundary pixels.
      ImageRegionIterator<typename BoundaryType::face_t> faceIt =
        ImageRegionIterator<typename BoundaryType::face_t>(face, region);
      ImageRegionIterator<OutputImageType> labelIt = ImageRegionIterator<OutputImageType>(output, region);
      faceIt.GoToBegin();
      labelIt.GoToBegin();
      while (!faceIt.IsAtEnd())
      {
        faceIt.Value().label = labelIt.Get();

        // Is this a flat region that flows out?
        const auto flrt_it = flatRegions.find(labelIt.Get());
        if (faceIt.Get().flow != NULL_FLOW && flrt_it != flatRegions.end())
        {
          // Have we already entered this
          // flat region into the boundary?
          const auto flats_it = flats->find(labelIt.Get());
          if (flats_it == flats->end()) // NO
          {
            typename BoundaryType::flat_region_t flr;
            flr.bounds_min = flrt_it->second.bounds_min;
            flr.min_label = *(flrt_it->second.min_label_ptr);
            flr.value = flrt_it->second.value;
            flr.offset_list.push_back(face->ComputeOffset(faceIt.GetIndex()));
            flats->insert(BoundaryFlatHashValueType(labelIt.Get(), flr));
            flr.offset_list.clear();
          }
          else // YES
          {
            flats_it->second.offset_list.push_back(face->ComputeOffset(faceIt.GetIndex()));
          }
        }

        ++faceIt;
        ++labelIt;
      }
    }
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::InitializeBoundary()
{
  typename BoundaryType::face_pixel_t fps;
  fps.flow = NULL_FLOW;
  fps.label = NULL_LABEL;

  BoundaryIndexType idx;
  for (idx.first = 0; idx.first < ImageDimension; ++(idx.first))
  {
    for (idx.second = 0; idx.second < 2; ++(idx.second))
    {
      if (this->GetBoundary()->GetValid(idx) == false)
      {
        continue;
      }
      this->GetBoundary()->GetFlatHash(idx)->clear();
      const typename BoundaryType::face_t::Pointer face = this->GetBoundary()->GetFace(idx);
      if (face != nullptr)
      {
        face->FillBuffer(fps);
      }
    }
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::AnalyzeBoundaryFlow(InputImageTypePointer thresholdImage,
                                            flat_region_table_t & flatRegions,
                                            InputPixelType        max)
{
  //
  // NOTE: For ease of initial implementation, this method does
  // not support arbitrary connectivity across boundaries (yet). 10-8-01 jc
  //
  bool isSteepest = false;

  typename BoundaryType::face_pixel_t fps;

  const typename OutputImageType::Pointer output = this->GetOutputImage();
  const typename BoundaryType::Pointer    boundary = this->GetBoundary();

  typename ConstNeighborhoodIterator<InputImageType>::RadiusType rad;
  for (unsigned int i = 0; i < ImageDimension; ++i)
  {
    rad[i] = 1;
  }
  fps.label = NULL_LABEL;

  auto eqTable = EquivalencyTable::New();

  // Process each boundary region.
  BoundaryIndexType idx;
  for (idx.first = 0; idx.first < ImageDimension; ++(idx.first))
  {
    for (idx.second = 0; idx.second < 2; ++(idx.second))
    {
      // Skip irrelevant boundaries
      if (boundary->GetValid(idx) == false)
      {
        continue;
      }

      const typename BoundaryType::face_t::Pointer face = boundary->GetFace(idx);
      const ImageRegionType                        region = face->GetRequestedRegion();

      ConstNeighborhoodIterator<InputImageType> searchIt =
        ConstNeighborhoodIterator<InputImageType>(rad, thresholdImage, region);
      NeighborhoodIterator<OutputImageType> labelIt = NeighborhoodIterator<OutputImageType>(rad, output, region);
      ImageRegionIterator<typename BoundaryType::face_t> faceIt =
        ImageRegionIterator<typename BoundaryType::face_t>(face, region);

      const unsigned int nCenter = searchIt.Size() / 2;
      searchIt.GoToBegin();
      labelIt.GoToBegin();

      const unsigned int cPos =
        ((idx).second == 0)
          ? /* Low face */ m_Connectivity.index[(idx).first]
          : /* High face */ m_Connectivity.index[(ImageDimension - 1) + (ImageDimension - (idx).first)];

      while (!searchIt.IsAtEnd())
      {
        // Is this a flat connection?
        if (Math::AlmostEquals(searchIt.GetPixel(nCenter), searchIt.GetPixel(cPos)))
        {
          // Fill in the boundary flow information.
          // Labels will be collected later.
          fps.flow = static_cast<short>(cPos);
          faceIt.Set(fps);

          // Are we touching flat regions
          // that have already been labeled?
          bool _labeled = false;
          bool _connected = false;
          for (unsigned int i = 0; i < m_Connectivity.size; ++i)
          {
            const unsigned int nPos = m_Connectivity.index[i];
            if (Math::AlmostEquals(searchIt.GetPixel(nCenter), searchIt.GetPixel(nPos)) &&
                labelIt.GetPixel(nPos) != Self::NULL_LABEL && labelIt.GetPixel(nPos) != labelIt.GetPixel(nCenter))
            {
              _connected = true;
              if (_labeled == false)
              {
                labelIt.SetPixel(nCenter, labelIt.GetPixel(nPos));
                _labeled = true;
              }
              else
              {
                eqTable->Add(labelIt.GetPixel(nCenter), labelIt.GetPixel(nPos));
              }
            }
          }
          if (_connected == false) // Add a new flat region.
          {
            labelIt.SetPixel(nCenter, m_CurrentLabel);

            // Add a flat region to the (global) flat region table
            flat_region_t tempFlatRegion;
            tempFlatRegion.bounds_min = max;
            tempFlatRegion.min_label_ptr = output->GetBufferPointer() + output->ComputeOffset(labelIt.GetIndex());
            tempFlatRegion.value = searchIt.GetPixel(nCenter);
            tempFlatRegion.is_on_boundary = true;
            flatRegions[m_CurrentLabel] = tempFlatRegion;

            ++m_CurrentLabel;
          }
        }
        else // Is cPos the path of steepest descent?
        {
          if (searchIt.GetPixel(cPos) < searchIt.GetPixel(nCenter))
          {
            isSteepest = true;
            for (unsigned int i = 0; i < m_Connectivity.size; ++i)
            {
              const unsigned int nPos = m_Connectivity.index[i];
              if (searchIt.GetPixel(nPos) < searchIt.GetPixel(cPos))
              {
                isSteepest = false;
                break;
              }
            }
          }
          else
          {
            isSteepest = false;
          }

          if (isSteepest)
          {
            // Label this pixel. It will be safely treated as a local
            // minimum by the rest of the segmentation algorithm.
            labelIt.SetPixel(nCenter, m_CurrentLabel);

            // Add the connectivity information
            // to the boundary data structure.
            fps.flow = static_cast<short>(cPos);
            faceIt.Set(fps);

            // Since we've labeled this pixel, we need to check to
            // make sure this is not also a flat region.  If it is,
            // then it must be entered into the flat region table
            // or we could have problems later on.
            for (unsigned int i = 0; i < m_Connectivity.size; ++i)
            {
              const unsigned int nPos = m_Connectivity.index[i];
              if (Math::AlmostEquals(searchIt.GetPixel(nPos), searchIt.GetPixel(nCenter)))
              {
                flat_region_t tempFlatRegion;
                tempFlatRegion.bounds_min = max;
                tempFlatRegion.min_label_ptr = output->GetBufferPointer() + output->ComputeOffset(labelIt.GetIndex());
                tempFlatRegion.value = searchIt.GetPixel(nCenter);
                tempFlatRegion.is_on_boundary = false;
                flatRegions[m_CurrentLabel] = tempFlatRegion;
                break;
              }
            }
            ++m_CurrentLabel;
          }
        }

        ++searchIt;
        ++labelIt;
        ++faceIt;
      }
    }
  }

  eqTable->Flatten();

  // Now relabel any equivalent regions in the boundaries.
  for (idx.first = 0; idx.first < ImageDimension; ++(idx.first))
  {
    for (idx.second = 0; idx.second < 2; ++(idx.second))
    {
      // Skip irrelevant boundaries
      if (boundary->GetValid(idx) == false)
      {
        continue;
      }

      const typename BoundaryType::face_t::Pointer face = boundary->GetFace(idx);
      const ImageRegionType                        region = face->GetRequestedRegion();

      Self::RelabelImage(output, region, eqTable);
    }
  }

  // Merge the flat regions in the table
  Self::MergeFlatRegions(flatRegions, eqTable);
}

template <typename TInputImage>
void
Segmenter<TInputImage>::GenerateConnectivity()
{
  //
  // Creates city-block style connectivity.  4-Neighbors in 2D.  6-Neighbors in
  // 3D, etc...  Order of creation MUST be lowest index to highest index in the
  // neighborhood.  I.e. for 4 connectivity,
  //
  //     * 1 *
  //     2 * 3
  //     * 4 *
  //
  // Algorithms assume this order to the connectivity.
  //
  typename ConstNeighborhoodIterator<InputImageType>::RadiusType rad;
  for (unsigned int i = 0; i < ImageDimension; ++i)
  {
    rad[i] = 1;
  }
  const ConstNeighborhoodIterator<InputImageType> it(
    rad, this->GetInputImage(), this->GetInputImage()->GetRequestedRegion());
  const unsigned int nSize = it.Size();
  const unsigned int nCenter = nSize >> 1;

  unsigned int i = 0;
  for (; i < m_Connectivity.size; ++i) // initialize move list
  {
    for (unsigned int j = 0; j < ImageDimension; ++j)
    {
      m_Connectivity.direction[i][j] = 0;
    }
  }
  i = 0;
  for (int d = ImageDimension - 1; d >= 0; d--)
  {
    const unsigned int stride = it.GetStride(d);
    m_Connectivity.index[i] = nCenter - stride;
    m_Connectivity.direction[i][d] = -1;
    ++i;
  }
  for (int d = 0; d < int{ ImageDimension }; ++d)
  {
    const unsigned int stride = it.GetStride(d);
    m_Connectivity.index[i] = nCenter + stride;
    m_Connectivity.direction[i][d] = 1;
    ++i;
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::LabelMinima(InputImageTypePointer                img,
                                    ImageRegionType                      region,
                                    typename Self::flat_region_table_t & flatRegions,
                                    InputPixelType                       Max)
{
  unsigned int         nPos = 0;
  const InputPixelType maxValue = Max;

  auto equivalentLabels = EquivalencyTable::New();

  const typename OutputImageType::Pointer output = this->GetOutputImage();

  // Set up the iterators.
  typename ConstNeighborhoodIterator<InputImageType>::RadiusType rad;
  for (unsigned int i = 0; i < ImageDimension; ++i)
  {
    rad[i] = 1;
  }
  ConstNeighborhoodIterator<InputImageType> searchIt(rad, img, region);
  NeighborhoodIterator<OutputImageType>     labelIt(rad, output, region);
  const unsigned int                        nSize = searchIt.Size();
  const unsigned int                        nCenter = nSize >> 1;

  // Sweep through the images.  Label all local minima
  // and record information for all the flat regions.
  for (searchIt.GoToBegin(), labelIt.GoToBegin(); !searchIt.IsAtEnd(); ++searchIt, ++labelIt)
  {
    bool foundSinglePixelMinimum = true;
    bool foundFlatRegion = false;

    // If this pixel has been labeled already,
    // skip directly to the next iteration.
    if (labelIt.GetPixel(nCenter) != Self::NULL_LABEL)
    {
      continue;
    }

    // Compare current pixel value with its neighbors.
    const InputPixelType currentValue = searchIt.GetPixel(nCenter);
    unsigned int         i = 0;
    for (; i < m_Connectivity.size; ++i)
    {
      nPos = m_Connectivity.index[i];
      if (Math::AlmostEquals(currentValue, searchIt.GetPixel(nPos)))
      {
        foundFlatRegion = true;
        break;
      }
      if (currentValue > searchIt.GetPixel(nPos))
      {
        foundSinglePixelMinimum = false;
      }
    }

    if (foundFlatRegion)
    {
      if (labelIt.GetPixel(nPos) != Self::NULL_LABEL) // If the flat region is
      // already
      {
        // labeled, label this
        // to match.
        labelIt.SetPixel(nCenter, labelIt.GetPixel(nPos));
      }
      else // Add a new flat region to the table.
      {
        // Initialize its contents.
        labelIt.SetPixel(nCenter, m_CurrentLabel);
        nPos = m_Connectivity.index[0];
        flat_region_t tempFlatRegion;
        tempFlatRegion.bounds_min = maxValue;
        tempFlatRegion.min_label_ptr = labelIt[nPos];
        tempFlatRegion.value = currentValue;
        flatRegions[m_CurrentLabel] = tempFlatRegion;
        m_CurrentLabel = m_CurrentLabel + 1;
      }

      // While we're at it, check to see if we have just linked two flat
      // regions with the same height value.  Save that info for later.
      for (i++; i < m_Connectivity.size; ++i)
      {
        nPos = m_Connectivity.index[i];
        if (Math::AlmostEquals(searchIt.GetPixel(nCenter), searchIt.GetPixel(nPos)) &&
            labelIt.GetPixel(nPos) != Self::NULL_LABEL && labelIt.GetPixel(nPos) != labelIt.GetPixel(nCenter))
        {
          equivalentLabels->Add(labelIt.GetPixel(nCenter), labelIt.GetPixel(nPos));
        }
      }
    }
    else if (foundSinglePixelMinimum)
    {
      labelIt.SetPixel(nCenter, m_CurrentLabel);
      m_CurrentLabel = m_CurrentLabel + 1;
    }
  }

  // Merge the flat regions that we identified as connected components.
  Self::MergeFlatRegions(flatRegions, equivalentLabels);

  // Relabel the image with the merged regions.
  Self::RelabelImage(output, region, equivalentLabels);

  equivalentLabels->Clear();

  // Now make another pass to establish the
  // boundary values for the flat regions.
  for (searchIt.GoToBegin(), labelIt.GoToBegin(); !searchIt.IsAtEnd(); ++searchIt, ++labelIt)
  {
    const auto flatPtr = flatRegions.find(labelIt.GetPixel(nCenter));
    if (flatPtr != flatRegions.end()) // If we are in a flat region
    {
      // Search the connectivity neighborhood
      // for lesser boundary pixels.
      for (unsigned int i = 0; i < m_Connectivity.size; ++i)
      {
        nPos = m_Connectivity.index[i];

        if (labelIt.GetPixel(nPos) != labelIt.GetPixel(nCenter) && searchIt.GetPixel(nPos) < flatPtr->second.bounds_min)
        {
          // If this is a boundary pixel && has a lesser value than
          // the currently recorded value...
          flatPtr->second.bounds_min = searchIt.GetPixel(nPos);
          flatPtr->second.min_label_ptr = labelIt[nPos];
        }
        if (Math::AlmostEquals(searchIt.GetPixel(nCenter), searchIt.GetPixel(nPos)))
        {
          if (labelIt.GetPixel(nPos) != NULL_LABEL)
          {
            // Pick up any equivalencies we missed before.
            equivalentLabels->Add(labelIt.GetPixel(nCenter), labelIt.GetPixel(nPos));
          }
          // If the following is encountered, it means that there is a
          // logic flaw in the first pass of this algorithm where flat
          // regions are initially detected and linked.
#ifndef NDEBUG
          else
          {
            itkDebugMacro("An unexpected but non-fatal error has occurred.");
          }
#endif
        }
      }
    }
  }

  // Merge the flat regions that we identified as connected components.
  Self::MergeFlatRegions(flatRegions, equivalentLabels);

  // Relabel the image with the merged regions.
  Self::RelabelImage(output, region, equivalentLabels);
}

template <typename TInputImage>
void
Segmenter<TInputImage>::GradientDescent(InputImageTypePointer img, ImageRegionType region)
{
  const typename OutputImageType::Pointer output = this->GetOutputImage();

  //
  // Set up our iterators.
  //
  typename ConstNeighborhoodIterator<InputImageType>::RadiusType rad;
  typename NeighborhoodIterator<OutputImageType>::RadiusType     zeroRad;
  for (unsigned int i = 0; i < ImageDimension; ++i)
  {
    rad[i] = 1;
    zeroRad[i] = 0;
  }
  ConstNeighborhoodIterator<InputImageType> valueIt(rad, img, region);
  NeighborhoodIterator<OutputImageType>     labelIt(zeroRad, output, region);

  //
  // Sweep through the image and trace all unlabeled
  // pixels to a labeled region
  //
  std::stack<IdentifierType *> updateStack;
  for (ImageRegionIterator<OutputImageType> it(output, region); !it.IsAtEnd(); ++it)
  {
    if (it.Get() == NULL_LABEL)
    {
      valueIt.SetLocation(it.GetIndex());
      labelIt.SetLocation(it.GetIndex());
      IdentifierType newLabel = NULL_LABEL; // Follow the path of steep-
      while (newLabel == NULL_LABEL)        // est descent until a label
      {
        // is found.
        updateStack.push(labelIt.GetCenterPointer());
        InputPixelType                      minVal = valueIt.GetPixel(m_Connectivity.index[0]);
        typename InputImageType::OffsetType moveIndex = m_Connectivity.direction[0];
        for (unsigned int ii = 1; ii < m_Connectivity.size; ++ii)
        {
          const unsigned int nPos = m_Connectivity.index[ii];
          if (valueIt.GetPixel(nPos) < minVal)
          {
            minVal = valueIt.GetPixel(nPos);
            moveIndex = m_Connectivity.direction[ii];
          }
        }
        valueIt += moveIndex;
        labelIt += moveIndex;
        newLabel = labelIt.GetPixel(0);
      }

      while (!updateStack.empty()) // Update all the pixels we've traversed
      {
        *(updateStack.top()) = newLabel;
        updateStack.pop();
      }
    }
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::DescendFlatRegions(flat_region_table_t & flatRegionTable, ImageRegionType imageRegion)
{
  const typename OutputImageType::Pointer output = this->GetOutputImage();
  // Assumes all pixels are labeled in the image.  Steps through the flat
  // regions and equates each one with the label at its lowest boundary
  // point. Flat basins are preserved as their own regions. The output image is
  // relabeled to reflect these equivalencies.
  auto equivalentLabels = EquivalencyTable::New();

  for (auto region = flatRegionTable.begin(); region != flatRegionTable.end(); ++region)
  {
    if ((region->second.bounds_min < region->second.value) && (!region->second.is_on_boundary))
    {
      equivalentLabels->Add(region->first, *(region->second.min_label_ptr));
    }
  }

  equivalentLabels->Flatten();
  Self::RelabelImage(output, imageRegion, equivalentLabels);
}

template <typename TInputImage>
void
Segmenter<TInputImage>::UpdateSegmentTable(InputImageTypePointer input, ImageRegionType region)
{
  // Grab the data we need.
  const typename OutputImageType::Pointer  output = this->GetOutputImage();
  const typename SegmentTableType::Pointer segments = this->GetSegmentTable();

  // Set up some iterators.
  typename NeighborhoodIterator<OutputImageType>::RadiusType hoodRadius;
  for (unsigned int i = 0; i < ImageDimension; ++i)
  {
    hoodRadius[i] = 1;
  }
  ConstNeighborhoodIterator<InputImageType> searchIt(hoodRadius, input, region);
  NeighborhoodIterator<OutputImageType>     labelIt(hoodRadius, output, region);

  const IdentifierType hoodCenter = searchIt.Size() >> 1;

  edge_table_hash_t edgeHash;
  for (searchIt.GoToBegin(), labelIt.GoToBegin(); !searchIt.IsAtEnd(); ++searchIt, ++labelIt)
  {
    const IdentifierType segment_label = labelIt.GetPixel(hoodCenter);

    // Find the segment corresponding to this label
    // and update its minimum value if necessary.

    typename SegmentTableType::segment_t * segment_ptr = segments->Lookup(segment_label);
    auto                                   edge_table_entry_ptr = edgeHash.find(segment_label);
    const edge_table_t                     tempEdgeTable;
    if (segment_ptr == nullptr) // This segment not yet identified.
    {
      // So add it to the table.
      typename SegmentTableType::segment_t temp_segment;
      temp_segment.min = searchIt.GetPixel(hoodCenter);
      segments->Add(segment_label, temp_segment);
      using ValueType = typename edge_table_hash_t::value_type;

      edgeHash.insert(ValueType(segment_label, tempEdgeTable));

      edge_table_entry_ptr = edgeHash.find(segment_label);
    }
    else if (searchIt.GetPixel(hoodCenter) < segment_ptr->min)
    {
      segment_ptr->min = searchIt.GetPixel(hoodCenter);
    }

    // Look up each neighboring segment in this segment's edge table.
    // If an edge exists, compare (and reset) the minimum edge value.
    // Note that edges are located *between* two adjacent pixels and
    // the value is taken to be the maximum of the two adjacent pixel
    // values.
    for (unsigned int i = 0; i < m_Connectivity.size; ++i)
    {
      const unsigned int nPos = m_Connectivity.index[i];
      InputPixelType     lowest_edge;
      if (labelIt.GetPixel(nPos) != segment_label && labelIt.GetPixel(nPos) != NULL_LABEL)
      {
        if (searchIt.GetPixel(nPos) < searchIt.GetPixel(hoodCenter))
        {
          lowest_edge = searchIt.GetPixel(hoodCenter); // We want the
        }
        else
        {
          lowest_edge = searchIt.GetPixel(nPos); // max of the
        }
        // adjacent pixels

        const auto edge_ptr = edge_table_entry_ptr->second.find(labelIt.GetPixel(nPos));
        if (edge_ptr == edge_table_entry_ptr->second.end())
        {
          // This edge has not been identified yet.
          using ValueType = typename edge_table_t::value_type;
          edge_table_entry_ptr->second.insert(ValueType(labelIt.GetPixel(nPos), lowest_edge));
        }
        else if (lowest_edge < edge_ptr->second)
        {
          edge_ptr->second = lowest_edge;
        }
      }
    }
  }

  //
  // Copy all of the edge tables into the edge lists of the
  // segment table.
  //
  for (auto edge_table_entry_ptr = edgeHash.begin(); edge_table_entry_ptr != edgeHash.end(); ++edge_table_entry_ptr)
  {
    // Lookup the corresponding segment entry
    typename SegmentTableType::segment_t * segment_ptr = segments->Lookup(edge_table_entry_ptr->first);
    if (segment_ptr == nullptr)
    {
      itkGenericExceptionMacro("UpdateSegmentTable:: An unexpected and fatal error has occurred.");
    }

    // Copy into the segment list
    const auto listsz = static_cast<IdentifierType>(edge_table_entry_ptr->second.size());
    segment_ptr->edge_list.resize(listsz);
    auto edge_ptr = edge_table_entry_ptr->second.begin();
    auto list_ptr = segment_ptr->edge_list.begin();
    while (edge_ptr != edge_table_entry_ptr->second.end())
    {
      list_ptr->label = edge_ptr->first;
      list_ptr->height = edge_ptr->second;
      ++edge_ptr;
      ++list_ptr;
    }

    // Clean up memory as we go
    edge_table_entry_ptr->second.clear();
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::BuildRetainingWall(InputImageTypePointer img, ImageRegionType region, InputPixelType value)
{
  // Loop through the dimensions and populate the LOW and HIGH faces regions.
  for (unsigned int i = 0; i < ImageDimension; ++i)
  {
    typename ImageRegionType::IndexType idx = region.GetIndex(); // LOW face
    typename ImageRegionType::SizeType  sz = region.GetSize();
    sz[i] = 1;
    ImageRegionType reg;
    reg.SetIndex(idx);
    reg.SetSize(sz);
    Segmenter::SetInputImageValues(img, reg, value);
    idx[i] = region.GetSize()[i] + region.GetIndex()[i] - 1; // HIGH face
    reg.SetIndex(idx);
    Segmenter::SetInputImageValues(img, reg, value);
  }
}

/*
  ----------------------------------------------------------------------------
  Algorithm helper methods and debugging methods
  ----------------------------------------------------------------------------
*/
template <typename TInputImage>
void
Segmenter<TInputImage>::SetInputImageValues(InputImageTypePointer img, ImageRegionType region, InputPixelType value)
{
  ImageRegionIterator<InputImageType> it(img, region);
  it.GoToBegin();
  while (!it.IsAtEnd())
  {
    it.Set(value);
    ++it;
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::SetOutputImageValues(OutputImageTypePointer img, ImageRegionType region, IdentifierType value)
{
  ImageRegionIterator<OutputImageType> it(img, region);
  it.GoToBegin();
  while (!it.IsAtEnd())
  {
    it.Set(value);
    ++it;
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::MinMax(InputImageTypePointer img,
                               ImageRegionType       region,
                               InputPixelType &      min,
                               InputPixelType &      max)
{
  ImageRegionIterator<InputImageType> it(img, region);
  it.GoToBegin();
  min = it.Value();
  max = it.Value();
  while (!it.IsAtEnd())
  {
    if (it.Get() > max)
    {
      max = it.Get();
    }
    if (it.Get() < min)
    {
      min = it.Get();
    }
    ++it;
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::MergeFlatRegions(flat_region_table_t & regions, EquivalencyTable::Pointer eqTable)
{
  // Note that the labels must have no interdependencies.  That is,
  // every key must map to a value that is not itself a key in the
  // table. This means that you must always merge label->first with
  // label->second (a to b). EquivalencyTable can be converted to this
  // format with its Flatten() method.
  eqTable->Flatten();

  for (auto it = eqTable->Begin(); it != eqTable->End(); ++it)
  {
    const auto a = regions.find(it->first);
    const auto b = regions.find(it->second);
    if ((a == regions.end()) || (b == regions.end()))
    {
      itkGenericExceptionMacro("MergeFlatRegions:: An unexpected and fatal error has occurred.");
    }

    if (a->second.bounds_min < b->second.bounds_min)
    {
      b->second.bounds_min = a->second.bounds_min;
      b->second.min_label_ptr = a->second.min_label_ptr;
    }

    regions.erase(a);
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::RelabelImage(OutputImageTypePointer    img,
                                     ImageRegionType           region,
                                     EquivalencyTable::Pointer eqTable)
{
  eqTable->Flatten();
  ImageRegionIterator<OutputImageType> it(img, region);

  it.GoToBegin();
  while (!it.IsAtEnd())
  {
    const IdentifierType temp = eqTable->Lookup(it.Get());
    if (temp != it.Get())
    {
      it.Set(temp);
    }
    ++it;
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::Threshold(InputImageTypePointer destination,
                                  InputImageTypePointer source,
                                  const ImageRegionType source_region,
                                  const ImageRegionType destination_region,
                                  InputPixelType        threshold)
{
  ImageRegionIterator<InputImageType> dIt(destination, destination_region);
  ImageRegionIterator<InputImageType> sIt(source, source_region);

  dIt.GoToBegin();
  sIt.GoToBegin();

  // Assumes that source_region and destination region are the same size.  Does
  // no checking!!
  if (NumericTraits<InputPixelType>::is_integer)
  {
    // integral data type, if any pixel is at the maximum possible
    // value for the data type, then drop the value by one intensity
    // value. This the watershed algorithm to construct a "barrier" or
    // "wall" around the image that will stop the watershed without
    // requiring an expensive boundary condition checks.
    while (!dIt.IsAtEnd())
    {
      const InputPixelType tmp = sIt.Get();
      ITK_GCC_PRAGMA_PUSH
      ITK_GCC_SUPPRESS_Wfloat_equal
      if (tmp < threshold)
      {
        dIt.Set(threshold);
      }
      else if (tmp == NumericTraits<InputPixelType>::max())
      {
        dIt.Set(tmp - NumericTraits<InputPixelType>::OneValue());
      }
      else
      {
        dIt.Set(tmp);
      }
      ITK_GCC_PRAGMA_POP
      ++dIt;
      ++sIt;
    }
  }
  else
  {
    // floating point data, no need to worry about overflow
    while (!dIt.IsAtEnd())
    {
      if (sIt.Get() < threshold)
      {
        dIt.Set(threshold);
      }
      else
      {
        dIt.Set(sIt.Get());
      }
      ++dIt;
      ++sIt;
    }
  }
}

/*
  ----------------------------------------------------------------------------
  Pipeline methods
  ----------------------------------------------------------------------------
*/
template <typename TInputImage>
auto
Segmenter<TInputImage>::MakeOutput(DataObjectPointerArraySizeType idx) -> DataObjectPointer
{
  if (idx == 0)
  {
    return OutputImageType::New().GetPointer();
  }
  if (idx == 1)
  {
    return SegmentTableType::New().GetPointer();
  }
  else if (idx == 2)
  {
    return BoundaryType::New().GetPointer();
  }
  else
  {
    return nullptr;
  }
}

template <typename TInputImage>
void
Segmenter<TInputImage>::UpdateOutputInformation()
{
  unsigned int i = 0;

  // call the superclass' implementation of this method
  Superclass::UpdateOutputInformation();

  // get pointers to the input and output
  const typename InputImageType::Pointer  inputPtr = this->GetInputImage();
  const typename OutputImageType::Pointer outputPtr = this->GetOutputImage();

  if (!inputPtr || !outputPtr)
  {
    return;
  }
  // we need to compute the output spacing, the output image size, and the
  // output image start index
  const typename InputImageType::SizeType &  inputSize = inputPtr->GetLargestPossibleRegion().GetSize();
  const typename InputImageType::IndexType & inputStartIndex = inputPtr->GetLargestPossibleRegion().GetIndex();

  typename OutputImageType::SizeType  outputSize;
  typename OutputImageType::IndexType outputStartIndex;

  for (i = 0; i < OutputImageType::ImageDimension; ++i)
  {
    outputSize[i] = inputSize[i];
    outputStartIndex[i] = inputStartIndex[i];
  }

  const typename OutputImageType::RegionType outputLargestPossibleRegion(outputStartIndex, outputSize);

  outputPtr->SetLargestPossibleRegion(outputLargestPossibleRegion);
}

template <typename TInputImage>
void
Segmenter<TInputImage>::GenerateInputRequestedRegion()
{
  // call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();

  // get pointers to the input and output
  const typename InputImageType::Pointer  inputPtr = this->GetInputImage();
  const typename OutputImageType::Pointer outputPtr = this->GetOutputImage();

  if (!inputPtr || !outputPtr)
  {
    return;
  }

  //
  // FOR NOW WE'LL JUST SET THE INPUT REGION TO THE OUTPUT REGION
  // AND OVERRIDE THIS LATER
  //
  inputPtr->SetRequestedRegion(outputPtr->GetRequestedRegion());
}

template <typename TInputImage>
void
Segmenter<TInputImage>::GenerateOutputRequestedRegion(DataObject * output)
{
  // Only the Image output need to be propagated through.
  // No choice but to use RTTI here.
  auto * imgData = dynamic_cast<ImageBase<ImageDimension> *>(output);

  if (imgData)
  {
    std::vector<ProcessObject::DataObjectPointer>::size_type idx = 0;
    for (idx = 0; idx < this->GetNumberOfIndexedOutputs(); ++idx)
    {

      if (this->GetOutput(idx) && this->GetOutput(idx) != output)
      {
        auto * op = dynamic_cast<ImageBase<ImageDimension> *>(this->GetOutput(idx));

        if (op)
        {
          this->GetOutput(idx)->SetRequestedRegion(output);
        }
      }
    }
  }
}

template <typename TInputImage>
Segmenter<TInputImage>::Segmenter()
  : m_SortEdgeLists(true)
  , m_MaximumFloodLevel(1.0)
  , m_CurrentLabel(1)
{
  m_Connectivity.direction = nullptr;
  m_Connectivity.index = nullptr;

  // Make the outputs (OutputImage, SegmentTable, Boundary).
  ProcessObject::MakeRequiredOutputs(*this, 3);

  // Allocate memory for connectivity
  m_Connectivity.size = 2 * ImageDimension;
  m_Connectivity.index = new unsigned int[m_Connectivity.size];
  m_Connectivity.direction = new typename InputImageType::OffsetType[m_Connectivity.size];
}

template <typename TInputImage>
void
Segmenter<TInputImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "SortEdgeLists: " << m_SortEdgeLists << std::endl;
  os << indent << "DoBoundaryAnalysis: " << m_DoBoundaryAnalysis << std::endl;
  os << indent << "Threshold: " << m_Threshold << std::endl;
  os << indent << "MaximumFloodLevel: " << m_MaximumFloodLevel << std::endl;
  os << indent << "CurrentLabel: " << m_CurrentLabel << std::endl;
}
} // namespace itk::watershed

#endif
