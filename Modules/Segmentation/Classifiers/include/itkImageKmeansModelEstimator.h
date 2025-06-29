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
#ifndef itkImageKmeansModelEstimator_h
#define itkImageKmeansModelEstimator_h

#include <ctime>
#include <cmath>
#include <cfloat>

#include "vnl/vnl_vector.h"
#include "vnl/vnl_matrix.h"
#include "itkMath.h"
#include "vnl/algo/vnl_matrix_inverse.h"

#include "itkImageRegionIterator.h"
#include "itkMacro.h"

#include "itkImageModelEstimatorBase.h"

constexpr int8_t ONEBAND = 1;
constexpr int8_t GLA_CONVERGED = 1;
constexpr int8_t GLA_NOT_CONVERGED = 2;
constexpr int8_t LBG_COMPLETED = 3;

namespace itk
{
/**
 * \class ImageKmeansModelEstimator
 * \brief Base class for ImageKmeansModelEstimator object.
 *
 * itkImageKmeansModelEstimator generates the kmeans model (cluster centers).
 * This object performs clustering of data sets into different clusters,
 * either using user-provided seed points as an initial guess or generating
 * the clusters using a recursive approach when the user provides the
 * number of desired clusters. Each cluster is represented by its cluster
 * center. The two algorithms used are the Generalized Lloyd
 * algorithm (GLA) and the Linde-Buzo-Gray algorithm (LBG). The cluster centers
 * are also referred to as codewords and a table of cluster centers
 * is referred as a codebook.
 *
 * As required by the GLA algorithm, the initial seed cluster should contain
 * approximate centers of clusters.  The GLA algorithm generates updated
 * cluster centers that result in a lower distortion than the input seed
 * cluster when the input vectors are mapped/classified/labelled using the
 * given codebooks.
 *
 * If no codebook is provided, the Linde-Buzo-Gray algorithm is used.
 * This algorithm uses the GLA algorithm at its core to generate the
 * centroids of the input vectors (data). However, since there is no initial
 * codebook, LBG first creates a one word codebook (or centroid of one
 * cluster comprising of all the input training vectors). The LBG uses
 * codeword or centroid splitting to create an increasing number of clusters.
 * Each new set of clusters are optimized using the GLA algorithm.
 * The number of clusters increases as $2^{n}$ n= 0, 1, ... The codebook
 * is expected to be in the form of a vnl matrix, where there are N rows,
 * each row representing the cluster mean of a given cluster. The number
 * of columns in the codebook should be equal to the input image vector
 * dimension.
 *
 * The threshold parameter controls the ''optimality'' of the returned
 * codebook, where optimality is related to the least possible
 * mean-squared error distortion that can be found by the algorithm.
 * For larger thresholds, the result will be less optimal.  For
 * smaller thresholds, the result will be more optimal.  If a more
 * optimal result is desired, then the algorithm will take longer to
 * complete. A reasonable threshold value is 0.01.
 *
 * If, during the operation of the algorithm, there are any unused
 * clusters or cells, the m_OffsetAdd and m_OffsetMultiply parameters are
 * used to split the cells with the highest distortion.  This
 * function will attempt to fill empty cells up to 10 times (unless
 * the overall distortion is zero). Using 0.01 is a reasonable default
 * values for the m_OffsetAdd and m_OffsetMultiply parameters.
 *
 * If the GLA is unable to resolve the data into the desired number of
 * clusters or cells, only the codewords which were used will be
 * returned.
 *
 * In terms of clustering, codewords are cluster centers, and a codebook
 * is a table containing all cluster centers.  The GLA produces results
 * that are equivalent to the K-means clustering algorithm.
 *
 * For more information about the algorithms, see \cite gersho1992.
 *
 * This object supports data handling of multiband images. The object
 * accepts the input image in vector format only, where each pixel is a
 * vector and each element of the vector corresponds to an entry from
 * 1 particular band of a multiband dataset. A single band image is treated
 * as a vector image with a single element for every vector.
 *
 * This function is templated over the type of input image. In
 * addition, a second parameter for the MembershipFunction needs to be
 * specified. In this case a Membership function that store cluster centroids
 * models needs to be specified.
 *
 * The Update() function enables the calculation of the various models, creates
 * the membership function objects and populates them.
 *
 * Note: There is a second implementation of k-means algorithm in ITK under the
 * itk::Statistics namespace. While this algorithm (GLA/LBG based algorithm) is
 * memory efficient, the other algorithm is time efficient.
 *
 * \sa KdTreeBasedKmeansEstimator, WeightedCentroidKdTreeGenerator, KdTree
 * \sa ScalarImageKmeansImageFilter
 *
 * \ingroup ClassificationFilters
 * \ingroup ITKClassifiers
 *
 * \sphinx
 * \sphinxexample{Segmentation/Classifiers/KMeansClusterOfPixelsInImage,K Means Cluster Of Pixels In Image}
 * \endsphinx
 */
template <typename TInputImage, typename TMembershipFunction>
class ITK_TEMPLATE_EXPORT ImageKmeansModelEstimator : public ImageModelEstimatorBase<TInputImage, TMembershipFunction>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImageKmeansModelEstimator);

  /** Standard class type aliases. */
  using Self = ImageKmeansModelEstimator;
  using Superclass = ImageModelEstimatorBase<TInputImage, TMembershipFunction>;

  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(ImageKmeansModelEstimator);

  /** Type definition for the input image. */
  using InputImageType = TInputImage;
  using InputImagePointer = typename TInputImage::Pointer;
  using InputImageConstPointer = typename TInputImage::ConstPointer;

  /** Type definition for the vector associated with
   * input image pixel type. */
  using InputImageVectorType = typename TInputImage::PixelType::VectorType;

  /** Type definition for the input image pixel type. */
  using InputImagePixelType = typename TInputImage::PixelType;

  /** Type definition for the input image iterator type. */
  using InputImageIterator = ImageRegionIterator<TInputImage>;

  using InputImageConstIterator = ImageRegionConstIterator<TInputImage>;

  /** Type definitions for the membership function . */
  using MembershipFunctionPointer = typename TMembershipFunction::Pointer;

  /** Type definition for a double matrix. */
  using CodebookMatrixOfDoubleType = vnl_matrix<double>;

  /** Type definition for an integer vector. */
  using CodebookMatrixOfIntegerType = vnl_matrix<int>;

  /** Set the cluster centers. */
  void
  SetCodebook(CodebookMatrixOfDoubleType inCodebook);

  /** Get the cluster centers. */
  itkGetConstMacro(Codebook, CodebookMatrixOfDoubleType);

  /** Get the optimized codebook or the centroids of the clusters. */
  CodebookMatrixOfDoubleType
  GetOutCodebook()
  {
    return m_Codebook;
  }

  /** Set/Get the threshold parameter. */
  /** @ITKStartGrouping */
  itkSetMacro(Threshold, double);
  itkGetConstMacro(Threshold, double);
  /** @ITKEndGrouping */
  /** Set/Get the offset add parameter. */
  /** @ITKStartGrouping */
  itkSetMacro(OffsetAdd, double);
  itkGetConstMacro(OffsetAdd, double);
  /** @ITKEndGrouping */
  /** Set/Get the offset multiplication parameter. */
  /** @ITKStartGrouping */
  itkSetMacro(OffsetMultiply, double);
  itkGetConstMacro(OffsetMultiply, double);
  /** @ITKEndGrouping */
  /** Set/Get the maximum number of attempts to split a codeword. */
  /** @ITKStartGrouping */
  itkSetMacro(MaxSplitAttempts, int);
  itkGetConstMacro(MaxSplitAttempts, int);
  /** @ITKEndGrouping */
  /** Return the codebook/cluster centers. */
  CodebookMatrixOfDoubleType
  GetKmeansResults()
  {
    return m_Centroid;
  }

protected:
  ImageKmeansModelEstimator();
  ~ImageKmeansModelEstimator() override = default;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  /** Starts the image modeling process */
  void
  GenerateData() override;

  /** Allocate memory for the output model. */
  void
  Allocate();

  /** Print out the results on the screen for visual feedback. */
  void
  PrintKmeansAlgorithmResults();

private:
  /** Generates the cluster centers (model) corresponding to the estimates of
   * the cluster centers (in the initial codebook).
   * If no codebook is provided, then use the number of classes to
   * determine the cluster centers or the Kmeans model. This is the
   * the base function to call the K-means classifier.
   * Takes the set of training images and internally computes the means and
   * variance of the various classes defined in the training set.
   */
  void
  EstimateModels() override;

  /** Estimate K-means models for the core function. */
  void
  EstimateKmeansModelParameters();

  using ImageSizeType = typename TInputImage::SizeType;

  /** Set up the vector to store the image  data. */
  using InputPixelVectorType = typename TInputImage::PixelType::VectorType;

  /**Reallocate various memories and then make a copy of the old data. */
  void
  Reallocate(int oldSize, int newSize);

  int
  WithCodebookUseGLA();

  int
  WithoutCodebookUseLBG();

  void
  NearestNeighborSearchBasic(double * distortion);

  void
  SplitCodewords(int currentSize, int numDesired, int scale);

  void
  Perturb(double * oldCodeword, int scale, double * newCodeword);

  CodebookMatrixOfDoubleType m_Codebook{};

  // Buffer for K-means calculations
  CodebookMatrixOfDoubleType m_Centroid{};

  double m_Threshold{};
  double m_OffsetAdd{};
  double m_OffsetMultiply{};
  int    m_MaxSplitAttempts{};

  bool   m_ValidInCodebook{};
  double m_DoubleMaximum{};
  double m_OutputDistortion{};
  int    m_OutputNumberOfEmptyCells{};

  SizeValueType m_VectorDimension{};
  SizeValueType m_NumberOfCodewords{};
  SizeValueType m_CurrentNumberOfCodewords{};

  CodebookMatrixOfIntegerType m_CodewordHistogram{};
  CodebookMatrixOfDoubleType  m_CodewordDistortion{};
}; // class ImageKmeansModelEstimator

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkImageKmeansModelEstimator.hxx"
#endif

#endif
