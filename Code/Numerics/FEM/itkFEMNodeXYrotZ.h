/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkFEMNodeXYrotZ.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

#ifndef __itkFEMNodeXYrotZ_h
#define __itkFEMNodeXYrotZ_h

#include "itkFEMNodeXY.h"

namespace itk {
namespace fem {




/**
 * \brief Node with 2 displacements and 1 rotation
 *
 * this node class is derived from NodeXY class. the additional component urotZ holds the displacement of rotation
 * about the Z axis. note that any element that requires nodes of class NodeXY, can also use this node class.
 * this way you can for example connect the Bar2D and Beam2D elements. (Bar2D requires NodeXY, while Beam2D adds a
 * rotation displacement and therefore requires NodeXYrotZ.
 */
class NodeXYrotZ : public NodeXY 
{
FEM_CLASS(NodeXYrotZ,Node)
public:

  /**
   * this node has 3 degrees fo freedom
   */
  enum { NDOF=3 };          

  /**
   * write the NodeXYrotZ to output stream
   */
  void Write( std::ostream& f, int ofid ) const;

  /**
   * Windows visualizatoion
   */
  #ifdef FEM_BUILD_VISUALIZATION
    void Draw(CDC* pDC) const;
  #endif

  NodeXYrotZ() : NodeXY() {}
  NodeXYrotZ(Float X_, Float Y_) : NodeXY(X_,Y_) {}

  /**
   * access to NDOF from base class
   */
  int N() const { return NDOF; };    

  /**
   * pointers to DOF displacements
   */
  Displacement* uDOF(int i) const 
    {  
    switch ( i ) 
      {
      case 0:
        return &uX;
        break;
      case 1:
        return &uY;
        break;
      case 2:
        return &urotZ;
        break;
      }
    /**
     * if DOF is out of range we return NULL pointer
     */
    return 0;
    
    };

  /**
   * even if the node is const, we must always be able to change the displacements
   */
  mutable Displacement urotZ;  

};

FEM_CLASS_INIT(NodeXYrotZ)




}} // end namespace itk::fem

#endif /* #ifndef __itkFEMNodeXYrotZ_h */
