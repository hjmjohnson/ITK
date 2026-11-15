# ==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          https://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
# ==========================================================================

import sys

import itk
import numpy as np


dimension = int(sys.argv[1])
image_size = 32
blob_sigma = 4.0
shift = 2.0
shrink_factors = [2, 1]
smoothing_sigmas = [1, 0]
iterations_per_level = [30, 30]
geometry_tolerance = 1e-6
center = np.full(dimension, (image_size - 1) / 2)
moving_center = center.copy()
moving_center[0] += shift
coordinates = np.indices((image_size,) * dimension, dtype=np.float32)


def blob(blob_center):
    squared_radius = sum(
        (coordinates[dimension - 1 - axis] - blob_center[axis]) ** 2
        for axis in range(dimension)
    )
    return itk.image_from_array(
        np.exp(-squared_radius / (2 * blob_sigma**2)).astype(np.float32)
    )


image = blob(center)
moving_image = blob(moving_center)
Image = type(image)
Transform = itk.DisplacementFieldTransform[itk.F, dimension]
Field = itk.Image[itk.Vector[itk.F, dimension], dimension]
Adaptor = itk.DisplacementFieldTransformParametersAdaptor[Transform]
AdaptorBase = itk.TransformParametersAdaptorBase[
    itk.Transform[itk.F, dimension, dimension]
]
Metric = itk.MattesMutualInformationImageToImageMetricv4[Image, Image, Image, itk.F]

double_registration = itk.SyNImageRegistrationMethod[Image, Image].New()
assert isinstance(
    double_registration.GetModifiableTransform(),
    itk.DisplacementFieldTransform[itk.D, dimension],
)

metric = Metric.New()
metric.SetNumberOfHistogramBins(20)
registration = itk.SyNImageRegistrationMethod[Image, Image, Transform].New(
    FixedImage=image, MovingImage=moving_image, Metric=metric
)

fields = []
for _ in range(2):
    field = Field.New()
    field.CopyInformation(image)
    field.SetRegions(image.GetBufferedRegion())
    field.AllocateInitialized()
    fields.append(field)
registration.SetInitialTransform(
    Transform.New(DisplacementField=fields[0], InverseDisplacementField=fields[1])
)
registration.SetNumberOfLevels(len(shrink_factors))
registration.SetShrinkFactorsPerLevel(shrink_factors)
registration.SetSmoothingSigmasPerLevel(smoothing_sigmas)
registration.SetNumberOfIterationsPerLevel(iterations_per_level)
registration.SetLearningRate(0.25)

adaptors = itk.vector[AdaptorBase]()
for factor in shrink_factors:
    shrink = itk.ShrinkImageFilter[Image, Image].New(Input=image, ShrinkFactors=factor)
    shrink.UpdateOutputInformation()
    level_image = shrink.GetOutput()
    adaptor = Adaptor.New()
    adaptor.SetRequiredSpacing(level_image.GetSpacing())
    adaptor.SetRequiredSize(level_image.GetLargestPossibleRegion().GetSize())
    adaptor.SetRequiredDirection(level_image.GetDirection())
    adaptor.SetRequiredOrigin(level_image.GetOrigin())
    adaptors.push_back(adaptor)
registration.SetTransformParametersAdaptorsPerLevel(adaptors)
assert len(registration.GetTransformParametersAdaptorsPerLevel()) == len(shrink_factors)
registration.Update()

transform = registration.GetModifiableTransform()
assert isinstance(transform, Transform)
mapped_center = np.array(transform.TransformPoint(center))
assert np.linalg.norm(mapped_center - moving_center) < shift / 2, mapped_center
mapped_moving_center = np.array(
    transform.GetInverseTransform().TransformPoint(moving_center)
)
assert np.linalg.norm(mapped_moving_center - center) < shift / 2, mapped_moving_center

for field in (
    transform.GetDisplacementField(),
    transform.GetInverseDisplacementField(),
):
    assert isinstance(field, Field)
    assert tuple(field.GetLargestPossibleRegion().GetSize()) == tuple(
        image.GetLargestPossibleRegion().GetSize()
    )
    np.testing.assert_allclose(
        field.GetOrigin(), image.GetOrigin(), atol=geometry_tolerance
    )
    np.testing.assert_allclose(
        field.GetSpacing(), image.GetSpacing(), atol=geometry_tolerance
    )
