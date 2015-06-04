/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkSyNImageRegistrationMethod_hxx
#define itkSyNImageRegistrationMethod_hxx

#include "itkSyNImageRegistrationMethod.h"

#include "itkComposeDisplacementFieldsImageFilter.h"
#include "itkGaussianOperator.h"
#include "itkImageMaskSpatialObject.h"
#include "itkImportImageFilter.h"
#include "itkInvertDisplacementFieldImageFilter.h"
#include "itkIterationReporter.h"
#include "itkMultiplyImageFilter.h"
#include "itkVectorNeighborhoodOperatorImageFilter.h"
#include "itkWindowConvergenceMonitoringFunction.h"

#include "itkDisplacementFieldTransformParametersAdaptor.h"

#include <iomanip>

namespace itk
{
/**
 * Constructor
 */
template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::SyNImageRegistrationMethod() :
  m_LearningRate( 0.25 ),
  m_ConvergenceThreshold( 1.0e-6 ),
  m_ConvergenceWindowSize( 10 ),
  m_GaussianSmoothingVarianceForTheUpdateField( 3.0 ),
  m_GaussianSmoothingVarianceForTheTotalField( 0.5 )
{
  this->m_NumberOfIterationsPerLevel.SetSize( 3 );
  this->m_NumberOfIterationsPerLevel[0] = 20;
  this->m_NumberOfIterationsPerLevel[1] = 30;
  this->m_NumberOfIterationsPerLevel[2] = 40;
  this->m_DownsampleImagesForMetricDerivatives = true;
  this->m_AverageMidPointGradients = false;
  this->m_FixedToMiddleTransform = ITK_NULLPTR;
  this->m_MovingToMiddleTransform = ITK_NULLPTR;
}

template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::~SyNImageRegistrationMethod()
{
}

template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
void
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::InitializeRegistrationAtEachLevel( const SizeValueType level )
{
  Superclass::InitializeRegistrationAtEachLevel( level );

  if( level == 0 )
    {
    // If FixedToMiddle and MovingToMiddle transforms are not set already for state restoration
    //
    if( this->m_FixedToMiddleTransform.IsNull() || this->m_MovingToMiddleTransform.IsNull() )
      {
      // Initialize the FixedToMiddleTransform as an Identity displacement field transform
      //
      this->m_FixedToMiddleTransform = OutputTransformType::New();
      this->m_MovingToMiddleTransform = OutputTransformType::New();

      VirtualImageBaseConstPointer virtualDomainImage = this->GetCurrentLevelVirtualDomainImage();

      const DisplacementVectorType zeroVector( 0.0 );

      typename DisplacementFieldType::Pointer fixedDisplacementField = DisplacementFieldType::New();
      fixedDisplacementField->CopyInformation( virtualDomainImage );
      fixedDisplacementField->SetRegions( virtualDomainImage->GetBufferedRegion() );
      fixedDisplacementField->Allocate();
      fixedDisplacementField->FillBuffer( zeroVector );

      typename DisplacementFieldType::Pointer fixedInverseDisplacementField = DisplacementFieldType::New();
      fixedInverseDisplacementField->CopyInformation( virtualDomainImage );
      fixedInverseDisplacementField->SetRegions( virtualDomainImage->GetBufferedRegion() );
      fixedInverseDisplacementField->Allocate();
      fixedInverseDisplacementField->FillBuffer( zeroVector );

      this->m_FixedToMiddleTransform->SetDisplacementField( fixedDisplacementField );
      this->m_FixedToMiddleTransform->SetInverseDisplacementField( fixedInverseDisplacementField );

      typename DisplacementFieldType::Pointer movingDisplacementField = DisplacementFieldType::New();
      movingDisplacementField->CopyInformation( virtualDomainImage );
      movingDisplacementField->SetRegions( virtualDomainImage->GetBufferedRegion() );
      movingDisplacementField->Allocate();
      movingDisplacementField->FillBuffer( zeroVector );

      typename DisplacementFieldType::Pointer movingInverseDisplacementField = DisplacementFieldType::New();
      movingInverseDisplacementField->CopyInformation( virtualDomainImage );
      movingInverseDisplacementField->SetRegions( virtualDomainImage->GetBufferedRegion() );
      movingInverseDisplacementField->Allocate();
      movingInverseDisplacementField->FillBuffer( zeroVector );

      this->m_MovingToMiddleTransform->SetDisplacementField( movingDisplacementField );
      this->m_MovingToMiddleTransform->SetInverseDisplacementField( movingInverseDisplacementField );
      }
    else
      {
      if( this->m_FixedToMiddleTransform->GetInverseDisplacementField()
         && this->m_MovingToMiddleTransform->GetInverseDisplacementField() )
         {
         itkDebugMacro( "SyN registration is initialized by restoring the state.");
         this->m_TransformParametersAdaptorsPerLevel[0]->SetTransform( this->m_MovingToMiddleTransform );
         this->m_TransformParametersAdaptorsPerLevel[0]->AdaptTransformParameters();
         this->m_TransformParametersAdaptorsPerLevel[0]->SetTransform( this->m_FixedToMiddleTransform );
         this->m_TransformParametersAdaptorsPerLevel[0]->AdaptTransformParameters();
         }
      else
        {
        itkExceptionMacro( "Invalid state restoration." );
        }
      }
    }
  else if( this->m_TransformParametersAdaptorsPerLevel[level] )
    {
    this->m_TransformParametersAdaptorsPerLevel[level]->SetTransform( this->m_MovingToMiddleTransform );
    this->m_TransformParametersAdaptorsPerLevel[level]->AdaptTransformParameters();
    this->m_TransformParametersAdaptorsPerLevel[level]->SetTransform( this->m_FixedToMiddleTransform );
    this->m_TransformParametersAdaptorsPerLevel[level]->AdaptTransformParameters();
    //TODO: These dimensions are not matching with below!  These dimensions were created with ShrinkImageFilter for
    //resampling were made with shrink image filter
    }
}

/*
 * Start the optimization at each level.  We just do a basic gradient descent operation.
 */
template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
void
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::StartOptimization()
{
  VirtualImageBaseConstPointer virtualDomainImage = this->GetCurrentLevelVirtualDomainImage();

  if( virtualDomainImage.IsNull() )
    {
    itkExceptionMacro( "The virtual domain image is not found." );
    }

  InitialTransformType* fixedInitialTransform = const_cast<InitialTransformType*>( this->GetFixedInitialTransform() );

  // Monitor the convergence
  typedef itk::Function::WindowConvergenceMonitoringFunction<RealType> ConvergenceMonitoringType;
  typename ConvergenceMonitoringType::Pointer convergenceMonitoring = ConvergenceMonitoringType::New();
  convergenceMonitoring->SetWindowSize( this->m_ConvergenceWindowSize );

  IterationReporter reporter( this, 0, 1 );

  while( this->m_CurrentIteration++ < this->m_NumberOfIterationsPerLevel[this->m_CurrentLevel] && !this->m_IsConverged )
    {
    typename CompositeTransformType::Pointer fixedComposite = CompositeTransformType::New();
    if ( fixedInitialTransform != ITK_NULLPTR )
      {
      fixedComposite->AddTransform( fixedInitialTransform );
      }
    fixedComposite->AddTransform( this->m_FixedToMiddleTransform->GetInverseTransform() );
    fixedComposite->FlattenTransformQueue();
    fixedComposite->SetOnlyMostRecentTransformToOptimizeOn();

    typename CompositeTransformType::Pointer movingComposite = CompositeTransformType::New();
    movingComposite->AddTransform( this->m_CompositeTransform );
    movingComposite->AddTransform( this->m_MovingToMiddleTransform->GetInverseTransform() );
    movingComposite->FlattenTransformQueue();
    movingComposite->SetOnlyMostRecentTransformToOptimizeOn();

    // Compute the update fields (to both moving and fixed images) and smooth

    MeasureType fixedMetricValue = 0.0;
    MeasureType movingMetricValue = 0.0;

    DisplacementFieldPointer fixedToMiddleSmoothUpdateField = this->ComputeUpdateField(
      this->m_FixedSmoothImages, this->m_FixedPointSets, fixedComposite,
      this->m_MovingSmoothImages, this->m_MovingPointSets, movingComposite,
      ITK_NULLPTR, movingMetricValue );

    DisplacementFieldPointer movingToMiddleSmoothUpdateField = this->ComputeUpdateField(
      this->m_MovingSmoothImages, this->m_MovingPointSets, movingComposite,
      this->m_FixedSmoothImages, this->m_FixedPointSets, fixedComposite,
      ITK_NULLPTR, fixedMetricValue );

    if ( this->m_AverageMidPointGradients )
      {
      ImageRegionIteratorWithIndex<DisplacementFieldType> ItF( fixedToMiddleSmoothUpdateField, fixedToMiddleSmoothUpdateField->GetLargestPossibleRegion() );
      for( ItF.GoToBegin(); !ItF.IsAtEnd(); ++ItF )
        {
        ItF.Set( ItF.Get() - movingToMiddleSmoothUpdateField->GetPixel( ItF.GetIndex() ) );
        movingToMiddleSmoothUpdateField->SetPixel( ItF.GetIndex(), -ItF.Get() );
        }
      }

    // Add the update field to both displacement fields (from fixed/moving to middle image) and then smooth

    typedef ComposeDisplacementFieldsImageFilter<DisplacementFieldType> ComposerType;

    typename ComposerType::Pointer fixedComposer = ComposerType::New();
    fixedComposer->SetDisplacementField( fixedToMiddleSmoothUpdateField );
    fixedComposer->SetWarpingField( this->m_FixedToMiddleTransform->GetDisplacementField() );
    fixedComposer->Update();
    //TODO:  fixedToMiddleSmoothUpdateField  does not match this->m_FixedToMiddleTransform->GetDisplacementField()
    //TODO:  Figure out where dimension for m_FixedToMiddleTransform are created.

    DisplacementFieldPointer fixedToMiddleSmoothTotalFieldTmp = this->GaussianSmoothDisplacementField(
      fixedComposer->GetOutput(), this->m_GaussianSmoothingVarianceForTheTotalField );

    typename ComposerType::Pointer movingComposer = ComposerType::New();
    movingComposer->SetDisplacementField( movingToMiddleSmoothUpdateField );
    movingComposer->SetWarpingField( this->m_MovingToMiddleTransform->GetDisplacementField() );
    movingComposer->Update();

    DisplacementFieldPointer movingToMiddleSmoothTotalFieldTmp = this->GaussianSmoothDisplacementField(
      movingComposer->GetOutput(), this->m_GaussianSmoothingVarianceForTheTotalField );

    // Iteratively estimate the inverse fields.

    DisplacementFieldPointer fixedToMiddleSmoothTotalFieldInverse = this->InvertDisplacementField( fixedToMiddleSmoothTotalFieldTmp, this->m_FixedToMiddleTransform->GetInverseDisplacementField() );
    DisplacementFieldPointer fixedToMiddleSmoothTotalField = this->InvertDisplacementField( fixedToMiddleSmoothTotalFieldInverse, fixedToMiddleSmoothTotalFieldTmp );

    DisplacementFieldPointer movingToMiddleSmoothTotalFieldInverse = this->InvertDisplacementField( movingToMiddleSmoothTotalFieldTmp, this->m_MovingToMiddleTransform->GetInverseDisplacementField() );
    DisplacementFieldPointer movingToMiddleSmoothTotalField = this->InvertDisplacementField( movingToMiddleSmoothTotalFieldInverse, movingToMiddleSmoothTotalFieldTmp );

    // Assign the displacement fields and their inverses to the proper transforms.
    this->m_FixedToMiddleTransform->SetDisplacementField( fixedToMiddleSmoothTotalField );
    this->m_FixedToMiddleTransform->SetInverseDisplacementField( fixedToMiddleSmoothTotalFieldInverse );

    this->m_MovingToMiddleTransform->SetDisplacementField( movingToMiddleSmoothTotalField );
    this->m_MovingToMiddleTransform->SetInverseDisplacementField( movingToMiddleSmoothTotalFieldInverse );

    this->m_CurrentMetricValue = 0.5 * ( movingMetricValue + fixedMetricValue );

    convergenceMonitoring->AddEnergyValue( this->m_CurrentMetricValue );
    this->m_CurrentConvergenceValue = convergenceMonitoring->GetConvergenceValue();

    if( this->m_CurrentConvergenceValue < this->m_ConvergenceThreshold )
      {
      this->m_IsConverged = true;
      }
    reporter.CompletedStep();
    }
}

template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
typename SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>::DisplacementFieldPointer
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::ComputeUpdateField( const FixedImagesContainerType fixedImages, const PointSetsContainerType fixedPointSets,
  const TransformBaseType * fixedTransform, const MovingImagesContainerType movingImages, const PointSetsContainerType movingPointSets,
  const TransformBaseType * movingTransform, const FixedImageMaskType * mask, MeasureType & value )
{

  for(size_t level = 0; level < this->m_TransformParametersAdaptorsPerLevel.size(); ++level)
    {
    typedef itk::DisplacementFieldTransformParametersAdaptor<DisplacementFieldTransformType> DisplacementFieldTransformAdaptorType;
    DisplacementFieldTransformAdaptorType * fieldTransformAdaptor =
    dynamic_cast<DisplacementFieldTransformAdaptorType *>(
                                                          this->m_TransformParametersAdaptorsPerLevel[level].GetPointer());
    if( fieldTransformAdaptor )
      {
      std::cout << std::fixed << std::setprecision(13) <<  "\nLEVEL_INITIALIALIZATION:   " << level << std::endl;
      std::cout << __FILE__ << " " << __LINE__ << "   FTA " << fieldTransformAdaptor->GetRequiredOrigin()
      << " " << fieldTransformAdaptor->GetRequiredSize()
      << " " << fieldTransformAdaptor->GetRequiredSpacing()<< std::endl;
      }
    else
      {
      std::cout << std::fixed << std::setprecision(13) <<  __FILE__ << " XXXXXXX " << __LINE__ << " Dynamic cast failed" << std::endl;
      }
    }
  DisplacementFieldPointer metricGradientField = this->ComputeMetricGradientField(
      fixedImages, fixedPointSets, fixedTransform, movingImages, movingPointSets, movingTransform, mask, value );
  std::cout << std::fixed << std::setprecision(13) << "ComputeUpdateField:" << std::endl;
  std::cout << __FILE__ << " " << __LINE__ << " m_VDI " << this->m_VirtualDomainImage->GetOrigin()
  << " " << this->m_VirtualDomainImage->GetLargestPossibleRegion().GetSize()
  << " " << this->m_VirtualDomainImage->GetSpacing()
  << std::endl;
  std::cout << __FILE__ << " " << __LINE__ << "  FI   " << fixedImages[0]->GetOrigin()
  << " " << fixedImages[0]->GetLargestPossibleRegion().GetSize()
  << " " << fixedImages[0]->GetSpacing()
  << std::endl;

  std::cout << __FILE__ << " " << __LINE__ << " mGF   " << metricGradientField->GetOrigin()
  << " " << metricGradientField->GetLargestPossibleRegion().GetSize()
  << " " << metricGradientField->GetSpacing()
  << std::endl;

  DisplacementFieldPointer updateField = this->GaussianSmoothDisplacementField( metricGradientField,
    this->m_GaussianSmoothingVarianceForTheUpdateField );

  DisplacementFieldPointer scaledUpdateField = this->ScaleUpdateField( updateField );
  std::cout << __FILE__ << " " << __LINE__ << " sUF   " << scaledUpdateField->GetOrigin()
  << " " << scaledUpdateField->GetLargestPossibleRegion().GetSize()
  << " " << scaledUpdateField->GetSpacing()
  << std::endl;
  std::cout << __FILE__ << " " << __LINE__ << "  UF   " << updateField->GetOrigin()
  << " " << updateField->GetLargestPossibleRegion().GetSize()
  << " " << updateField->GetSpacing()
  << std::endl;

  std::cout << __FILE__ << " " << __LINE__ << " F2M   " << this->m_FixedToMiddleTransform->GetDisplacementField()->GetOrigin()
  << " " << this->m_FixedToMiddleTransform->GetDisplacementField()->GetLargestPossibleRegion().GetSize()
  << " " << this->m_FixedToMiddleTransform->GetDisplacementField()->GetSpacing()
  << std::endl;
  std::cout << __FILE__ << " " << __LINE__ << " M2M   " << this->m_MovingToMiddleTransform->GetDisplacementField()->GetOrigin()
  << " " << this->m_MovingToMiddleTransform->GetDisplacementField()->GetLargestPossibleRegion().GetSize()
  << " " << this->m_MovingToMiddleTransform->GetDisplacementField()->GetSpacing()
  << std::endl;


  return scaledUpdateField;
}

template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
typename SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>::DisplacementFieldPointer
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::ComputeMetricGradientField( const FixedImagesContainerType fixedImages, const PointSetsContainerType fixedPointSets,
  const TransformBaseType * fixedTransform, const MovingImagesContainerType movingImages, const PointSetsContainerType movingPointSets,
  const TransformBaseType * movingTransform, const FixedImageMaskType * itkNotUsed( mask ), MeasureType & value )
{
  typename MultiMetricType::Pointer multiMetric = dynamic_cast<MultiMetricType *>( this->m_Metric.GetPointer() );

  VirtualImageBaseConstPointer virtualDomainImage = this->GetCurrentLevelVirtualDomainImage();

  std::cout << std::fixed << std::setprecision(13) << __FILE__ << " " << __LINE__ << " RESPL " << virtualDomainImage->GetOrigin()
  << " " << virtualDomainImage->GetLargestPossibleRegion().GetSize()
  << " " << virtualDomainImage->GetSpacing()
  << std::endl;


  if( multiMetric )
    {
    for( SizeValueType n = 0; n < multiMetric->GetNumberOfMetrics(); n++ )
      {
      if( multiMetric->GetMetricQueue()[n]->GetMetricCategory() == MetricType::POINT_SET_METRIC )
        {
        multiMetric->GetMetricQueue()[n]->SetFixedObject( fixedPointSets[n] );
        multiMetric->GetMetricQueue()[n]->SetMovingObject( movingPointSets[n] );
        multiMetric->SetFixedTransform( const_cast<TransformBaseType *>( fixedTransform ) );
        multiMetric->SetMovingTransform( const_cast<TransformBaseType *>( movingTransform ) );

        dynamic_cast<PointSetMetricType *>( multiMetric->GetMetricQueue()[n].GetPointer() )->SetCalculateValueAndDerivativeInTangentSpace( true );
        }
      else if( multiMetric->GetMetricQueue()[n]->GetMetricCategory() == MetricType::IMAGE_METRIC )
        {
        if( !this->m_DownsampleImagesForMetricDerivatives )
          {
          multiMetric->GetMetricQueue()[n]->SetFixedObject( fixedImages[n] );
          multiMetric->GetMetricQueue()[n]->SetMovingObject( movingImages[n] );

          multiMetric->SetFixedTransform( const_cast<TransformBaseType *>( fixedTransform ) );
          multiMetric->SetMovingTransform( const_cast<TransformBaseType *>( movingTransform ) );
          }
        else
          {
          typedef ResampleImageFilter<FixedImageType, FixedImageType, RealType> FixedResamplerType;
          typename FixedResamplerType::Pointer fixedResampler = FixedResamplerType::New();
          fixedResampler->SetInput( fixedImages[n] );
          fixedResampler->SetTransform( fixedTransform );
          fixedResampler->UseReferenceImageOn();
          fixedResampler->SetReferenceImage( virtualDomainImage );
          fixedResampler->SetDefaultPixelValue( 0 );
          fixedResampler->Update();

          typedef ResampleImageFilter<MovingImageType, MovingImageType, RealType> MovingResamplerType;
          typename MovingResamplerType::Pointer movingResampler = MovingResamplerType::New();
          movingResampler->SetInput( movingImages[n] );
          movingResampler->SetTransform( movingTransform );
          movingResampler->UseReferenceImageOn();
          movingResampler->SetReferenceImage( virtualDomainImage );
          movingResampler->SetDefaultPixelValue( 0 );
          movingResampler->Update();

          multiMetric->GetMetricQueue()[n]->SetFixedObject( fixedResampler->GetOutput() );
          multiMetric->GetMetricQueue()[n]->SetMovingObject( movingResampler->GetOutput() );
          }
        }
      else
        {
        itkExceptionMacro( "Invalid metric." );
        }
      }
    }
  else
    {
    if( this->m_Metric->GetMetricCategory() == MetricType::POINT_SET_METRIC )
      {
      this->m_Metric->SetFixedObject( fixedPointSets[0] );
      this->m_Metric->SetMovingObject( movingPointSets[0] );

      dynamic_cast<PointSetMetricType *>( this->m_Metric.GetPointer() )->SetFixedTransform( const_cast<TransformBaseType *>( fixedTransform ) );
      dynamic_cast<PointSetMetricType *>( this->m_Metric.GetPointer() )->SetMovingTransform( const_cast<TransformBaseType *>( movingTransform ) );

      dynamic_cast<PointSetMetricType *>( this->m_Metric.GetPointer() )->SetCalculateValueAndDerivativeInTangentSpace( true );
      }
    else if( this->m_Metric->GetMetricCategory() == MetricType::IMAGE_METRIC )
      {
      if( !this->m_DownsampleImagesForMetricDerivatives )
        {
        this->m_Metric->SetFixedObject( fixedImages[0] );
        this->m_Metric->SetMovingObject( movingImages[0] );
        dynamic_cast<ImageMetricType *>( this->m_Metric.GetPointer() )->SetFixedTransform( const_cast<TransformBaseType *>( fixedTransform ) );
        dynamic_cast<ImageMetricType *>( this->m_Metric.GetPointer() )->SetMovingTransform( const_cast<TransformBaseType *>( movingTransform ) );
        }
      else
        {
        typedef ResampleImageFilter<FixedImageType, FixedImageType, RealType> FixedResamplerType;
        typename FixedResamplerType::Pointer fixedResampler = FixedResamplerType::New();
        fixedResampler->SetInput( fixedImages[0] );
        fixedResampler->SetTransform( fixedTransform );
        fixedResampler->UseReferenceImageOn();
        fixedResampler->SetReferenceImage( virtualDomainImage );
        fixedResampler->SetDefaultPixelValue( 0 );
        fixedResampler->Update();

        typedef ResampleImageFilter<MovingImageType, MovingImageType, RealType> MovingResamplerType;
        typename MovingResamplerType::Pointer movingResampler = MovingResamplerType::New();
        movingResampler->SetInput( movingImages[0] );
        movingResampler->SetTransform( movingTransform );
        movingResampler->UseReferenceImageOn();
        movingResampler->SetReferenceImage( virtualDomainImage );
        movingResampler->SetDefaultPixelValue( 0 );
        movingResampler->Update();

        this->m_Metric->SetFixedObject( fixedResampler->GetOutput() );
        this->m_Metric->SetMovingObject( movingResampler->GetOutput() );
        }
      }
    else
      {
      itkExceptionMacro( "Invalid metric." );
      }
    }

  if( this->m_DownsampleImagesForMetricDerivatives && this->m_Metric->GetMetricCategory() != MetricType::POINT_SET_METRIC )
    {
    const DisplacementVectorType zeroVector( 0.0 );

    typename DisplacementFieldType::Pointer identityField = DisplacementFieldType::New();
    identityField->CopyInformation( virtualDomainImage );
    identityField->SetRegions( virtualDomainImage->GetLargestPossibleRegion() );
    identityField->Allocate();
    identityField->FillBuffer( zeroVector );

    DisplacementFieldTransformPointer identityDisplacementFieldTransform = DisplacementFieldTransformType::New();
    identityDisplacementFieldTransform->SetDisplacementField( identityField );
    identityDisplacementFieldTransform->SetInverseDisplacementField( identityField );

    if( this->m_Metric->GetMetricCategory() == MetricType::MULTI_METRIC )
      {
      multiMetric->SetFixedTransform( identityDisplacementFieldTransform );
      multiMetric->SetMovingTransform( identityDisplacementFieldTransform );
      }
    else if( this->m_Metric->GetMetricCategory() == MetricType::IMAGE_METRIC )
      {
      dynamic_cast<ImageMetricType *>( this->m_Metric.GetPointer() )->SetFixedTransform( identityDisplacementFieldTransform );
      dynamic_cast<ImageMetricType *>( this->m_Metric.GetPointer() )->SetMovingTransform( identityDisplacementFieldTransform );
      }
    }

  this->m_Metric->Initialize();

  typedef typename ImageMetricType::DerivativeType MetricDerivativeType;
  const typename MetricDerivativeType::SizeValueType metricDerivativeSize = virtualDomainImage->GetLargestPossibleRegion().GetNumberOfPixels() * ImageDimension;
  MetricDerivativeType metricDerivative( metricDerivativeSize );

  metricDerivative.Fill( NumericTraits<typename MetricDerivativeType::ValueType>::ZeroValue() );
  this->m_Metric->GetValueAndDerivative( value, metricDerivative );

  // Ensure that the size of the optimizer weights is the same as the
  // number of local transform parameters (=ImageDimension)
  if( !this->m_OptimizerWeightsAreIdentity && this->m_OptimizerWeights.Size() == ImageDimension )
    {
    typename MetricDerivativeType::iterator it;
    for( it = metricDerivative.begin(); it != metricDerivative.end(); it += ImageDimension )
      {
      for( unsigned int d = 0; d < ImageDimension; d++ )
        {
        *(it + d) *= this->m_OptimizerWeights[d];
        }
      }
    }

  // we rescale the update velocity field at each time point.
  // we first need to convert to a displacement field to look
  // at the max norm of the field.

  typename DisplacementFieldType::Pointer gradientField = DisplacementFieldType::New();
  gradientField->CopyInformation( virtualDomainImage );
  gradientField->SetRegions( virtualDomainImage->GetRequestedRegion() );
  gradientField->Allocate();

  ImageRegionIterator<DisplacementFieldType> ItG( gradientField, gradientField->GetRequestedRegion() );

  SizeValueType count = 0;
  for( ItG.GoToBegin(); !ItG.IsAtEnd(); ++ItG )
    {
    DisplacementVectorType displacement;
    for( SizeValueType d = 0; d < ImageDimension; d++ )
      {
      displacement[d] = metricDerivative[count++];
      }
    ItG.Set( displacement );
    }

  return gradientField;
}

template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
typename SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>::DisplacementFieldPointer
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::ScaleUpdateField( const DisplacementFieldType * updateField )
{
  typename DisplacementFieldType::SpacingType spacing = updateField->GetSpacing();
  ImageRegionConstIterator<DisplacementFieldType> ItF( updateField, updateField->GetLargestPossibleRegion() );

  RealType maxNorm = NumericTraits<RealType>::NonpositiveMin();
  for( ItF.GoToBegin(); !ItF.IsAtEnd(); ++ItF )
    {
    DisplacementVectorType vector = ItF.Get();

    RealType localNorm = 0;
    for( SizeValueType d = 0; d < ImageDimension; d++ )
      {
      localNorm += vnl_math_sqr( vector[d] / spacing[d] );
      }
    localNorm = std::sqrt( localNorm );

    if( localNorm > maxNorm )
      {
      maxNorm = localNorm;
      }
    }

  RealType scale = this->m_LearningRate;
  if( maxNorm > NumericTraits<RealType>::ZeroValue() )
    {
    scale /= maxNorm;
    }

  typedef Image<RealType, ImageDimension> RealImageType;

  typedef MultiplyImageFilter<DisplacementFieldType, RealImageType, DisplacementFieldType> MultiplierType;
  typename MultiplierType::Pointer multiplier = MultiplierType::New();
  multiplier->SetInput( updateField );
  multiplier->SetConstant( scale );

  typename DisplacementFieldType::Pointer scaledUpdateField = multiplier->GetOutput();
  scaledUpdateField->Update();
  scaledUpdateField->DisconnectPipeline();

  return scaledUpdateField;
}

template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
typename SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>::DisplacementFieldPointer
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::InvertDisplacementField( const DisplacementFieldType * field, const DisplacementFieldType * inverseFieldEstimate )
{
  typedef InvertDisplacementFieldImageFilter<DisplacementFieldType> InverterType;

  typename InverterType::Pointer inverter = InverterType::New();
  inverter->SetInput( field );
  inverter->SetInverseFieldInitialEstimate( inverseFieldEstimate );
  inverter->SetMaximumNumberOfIterations( 20 );
  inverter->SetMeanErrorToleranceThreshold( 0.001 );
  inverter->SetMaxErrorToleranceThreshold( 0.1 );
  inverter->Update();

  DisplacementFieldPointer inverseField = inverter->GetOutput();

  return inverseField;
}

template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
typename SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>::DisplacementFieldPointer
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::GaussianSmoothDisplacementField( const DisplacementFieldType * field, const RealType variance )
{
  typedef ImageDuplicator<DisplacementFieldType> DuplicatorType;
  typename DuplicatorType::Pointer duplicator = DuplicatorType::New();
  duplicator->SetInputImage( field );
  duplicator->Update();

  DisplacementFieldPointer smoothField = duplicator->GetModifiableOutput();

  if( variance <= 0.0 )
    {
    return smoothField;
    }

  typedef GaussianOperator<RealType, ImageDimension> GaussianSmoothingOperatorType;
  GaussianSmoothingOperatorType gaussianSmoothingOperator;

  typedef VectorNeighborhoodOperatorImageFilter<DisplacementFieldType, DisplacementFieldType> GaussianSmoothingSmootherType;
  typename GaussianSmoothingSmootherType::Pointer smoother = GaussianSmoothingSmootherType::New();

  for( SizeValueType d = 0; d < ImageDimension; d++ )
    {
    // smooth along this dimension
    gaussianSmoothingOperator.SetDirection( d );
    gaussianSmoothingOperator.SetVariance( variance );
    gaussianSmoothingOperator.SetMaximumError( 0.001 );
    gaussianSmoothingOperator.SetMaximumKernelWidth( smoothField->GetRequestedRegion().GetSize()[d] );
    gaussianSmoothingOperator.CreateDirectional();

    // todo: make sure we only smooth within the buffered region
    smoother->SetOperator( gaussianSmoothingOperator );
    smoother->SetInput( smoothField );
    try
      {
      smoother->Update();
      }
    catch( ExceptionObject & exc )
      {
      std::string msg( "Caught exception: " );
      msg += exc.what();
      itkExceptionMacro( << msg );
      }

    smoothField = smoother->GetOutput();
    smoothField->Update();
    smoothField->DisconnectPipeline();
    }

  const DisplacementVectorType zeroVector( 0.0 );

  //make sure boundary does not move
  RealType weight1 = 1.0;
  if( variance < 0.5 )
    {
    weight1 = 1.0 - 1.0 * ( variance / 0.5 );
    }
  RealType weight2 = 1.0 - weight1;

  const typename DisplacementFieldType::RegionType region = field->GetLargestPossibleRegion();
  const typename DisplacementFieldType::SizeType size = region.GetSize();
  const typename DisplacementFieldType::IndexType startIndex = region.GetIndex();

  ImageRegionConstIteratorWithIndex<DisplacementFieldType> ItF( field, field->GetLargestPossibleRegion() );
  ImageRegionIteratorWithIndex<DisplacementFieldType> ItS( smoothField, smoothField->GetLargestPossibleRegion() );
  for( ItF.GoToBegin(), ItS.GoToBegin(); !ItF.IsAtEnd(); ++ItF, ++ItS )
    {
    typename DisplacementFieldType::IndexType index = ItF.GetIndex();
    bool isOnBoundary = false;
    for ( unsigned int d = 0; d < ImageDimension; d++ )
      {
      if( index[d] == startIndex[d] || index[d] == static_cast<IndexValueType>( size[d] ) - startIndex[d] - 1 )
        {
        isOnBoundary = true;
        break;
        }
      }
    if( isOnBoundary )
      {
      ItS.Set( zeroVector );
      }
    else
      {
      ItS.Set( ItS.Get() * weight1 + ItF.Get() * weight2 );
      }
    }

  return smoothField;
}

/*
 * Start the registration
 */
template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
void
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::GenerateData()
{
  this->AllocateOutputs();

  for( this->m_CurrentLevel = 0; this->m_CurrentLevel < this->m_NumberOfLevels; this->m_CurrentLevel++ )
    {
    this->InitializeRegistrationAtEachLevel( this->m_CurrentLevel );

    // The base class adds the transform to be optimized at initialization.
    // However, since this class handles its own optimization, we remove it
    // to optimize separately.  We then add it after the optimization loop.

    this->m_CompositeTransform->RemoveTransform();

    this->StartOptimization();

    this->m_CompositeTransform->AddTransform( this->m_OutputTransform );
    }

  typedef ComposeDisplacementFieldsImageFilter<DisplacementFieldType, DisplacementFieldType> ComposerType;

  typename ComposerType::Pointer composer = ComposerType::New();
  composer->SetDisplacementField( this->m_MovingToMiddleTransform->GetInverseDisplacementField() );
  composer->SetWarpingField( this->m_FixedToMiddleTransform->GetDisplacementField() );
  composer->Update();

  typename ComposerType::Pointer inverseComposer = ComposerType::New();
  inverseComposer->SetDisplacementField( this->m_FixedToMiddleTransform->GetInverseDisplacementField() );
  inverseComposer->SetWarpingField( this->m_MovingToMiddleTransform->GetDisplacementField() );
  inverseComposer->Update();

  this->m_OutputTransform->SetDisplacementField( composer->GetOutput() );
  this->m_OutputTransform->SetInverseDisplacementField( inverseComposer->GetOutput() );

  this->GetTransformOutput()->Set(this->m_OutputTransform);
}

/*
 * PrintSelf
 */
template<typename TFixedImage, typename TMovingImage, typename TOutputTransform, typename TVirtualImage, typename TPointSet>
void
SyNImageRegistrationMethod<TFixedImage, TMovingImage, TOutputTransform, TVirtualImage, TPointSet>
::PrintSelf( std::ostream & os, Indent indent ) const
{
  Superclass::PrintSelf( os, indent );

  os << indent << "Number of current iterations per level: " << this->m_NumberOfIterationsPerLevel << std::endl;
  os << indent << "Learning rate: " << this->m_LearningRate << std::endl;
  os << indent << "Convergence threshold: " << this->m_ConvergenceThreshold << std::endl;
  os << indent << "Convergence window size: " << this->m_ConvergenceWindowSize << std::endl;
  os << indent << "Gaussian smoothing variance for the update field: " << this->m_GaussianSmoothingVarianceForTheUpdateField << std::endl;
  os << indent << "Gaussian smoothing variance for the total field: " << this->m_GaussianSmoothingVarianceForTheTotalField << std::endl;
}

} // end namespace itk

#endif
