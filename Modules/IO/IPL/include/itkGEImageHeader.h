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
/*=========================================================================
 *
 *  Portions of this file are subject to the VTK Toolkit Version 3 copyright.
 *
 *  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 *
 *  For complete copyright, license and disclaimer of warranty information
 *  please refer to the NOTICE file at the top of the ITK source tree.
 *
 *=========================================================================*/
#ifndef itkGEImageHeader_h
#define itkGEImageHeader_h
#include "ITKIOIPLExport.h"

#include "itkIOCommon.h"
#include "itkAnatomicalOrientation.h"

enum GE_PANE_STRUCT
{
  GE_AXIAL = 2,
  GE_SAGITTAL = 4,
  GE_CORONAL = 8
};

struct GEImageHeader
{
  short examNumber;
  short seriesNumber;
  short numberOfEchoes;
  short echoNumber;
  short imageNumber;
  float sliceLocation;
  float sliceThickness;
  float sliceGap;
  float TI;
  float TE;
  float TE2;
  float TR;
  short flipAngle;
  int   NEX;
  float xFOV;
  float yFOV;
  float centerR;
  float centerA;
  float centerS;
  float normR;
  float normA;
  float normS;
  float tlhcR;
  float tlhcA;
  float tlhcS;
  float trhcR;
  float trhcA;
  float trhcS;
  float brhcR;
  float brhcA;
  float brhcS;

  short acqXsize;
  short acqYsize;
  short frequencyDir;
  char  scanner[16];
  char  pulseSequence[128]; // Needs to be at least 65 for seimens vision
  char  patientId[32];
  char  scanId[32];
  char  name[64];
  char  date[32];
  short imageXsize;
  short imageYsize;
  float imageXres;
  float imageYres;

  itk::AnatomicalOrientation::PositiveEnum coordinateOrientation; // uint32_t

  short numberOfSlices;
  short offset;
  char  filename[itk::IOCommon::ITK_MAXPATHLEN + 1];
  char  hospital[35];
  char  modality[4];
  short imagesPerSlice;
  short turboFactor; // This is only relevant for the geADW image format, but
                     // is put here for convenience
};
#endif
