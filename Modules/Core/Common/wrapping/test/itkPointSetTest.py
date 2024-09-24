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
# ==========================================================================*/

import itk
import unittest
import numpy as np

class PointSetTestCase(unittest.TestCase):
    """Tests itk.PointSet"""

    def test_SetPointsByCoordinates_from_NumPy_array(self) -> None:
        """Tests the SetPointsByCoordinates method, having a NumPy array as input"""

        # The pixel type is irrelevant for this test, just use unsigned char.
        PixelType = itk.UC

        # Test the most common dimensions, and a few different numbers as number of points.
        for dimension in [2, 3]:
            for number_of_points in [1, 4, 9]:
                # Create a NumPy array of random coordinates between -1.0 and 1.0
                np_array = 2.0 * np.random.rand(number_of_points * dimension) - 1.0

                point_set = itk.PointSet[PixelType, dimension].New()
                point_set.SetPointsByCoordinates(np_array)

                points = point_set.GetPoints()

                self.assertEqual(points.Size(), number_of_points)

                for i in range(number_of_points):
                    point = points.GetElement(i)
                    for j in range(dimension):
                        self.assertAlmostEqual(point[j], np_array[i * dimension + j])


if __name__ == "__main__":
    unittest.main()
