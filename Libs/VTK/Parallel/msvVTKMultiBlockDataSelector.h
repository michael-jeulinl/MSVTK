/*==============================================================================

  Library: MSVTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// .NAME msvVTKMultiBlockDataSelector -
//

#ifndef __msvVTKMultiBlockDataSelector_h
#define __msvVTKMultiBlockDataSelector_h

// VTK_PARALLEL includes
#include "msvVTKParallelExport.h"

#include "vtkMultiBlockDataSetAlgorithm.h"

class msvVTKMultiBlockDataSelectorInternal;

class MSV_VTK_PARALLEL_EXPORT msvVTKMultiBlockDataSelector :
  public vtkMultiBlockDataSetAlgorithm
{
public:
  vtkTypeMacro(msvVTKMultiBlockDataSelector,vtkMultiBlockDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Construct object with PointIds and CellIds on; and ids being generated
  // as scalars.
  static msvVTKMultiBlockDataSelector *New();

  int SetDefaultLOD(int port, unsigned int lod);
  int SetDefaultLOD(vtkInformation *info, unsigned int lod);

  int SetHigherLOD(int flatIndex){return 0;}
  int SetLowerLOD(int flatIndex){return 0;}
  int GetNumberOfLOD(int flatIndex){return 0;}

protected:
  msvVTKMultiBlockDataSelector();
  ~msvVTKMultiBlockDataSelector();

  virtual int RequestUpdateExtent(vtkInformation*,
                                  vtkInformationVector**,
                                  vtkInformationVector*);

private:
  msvVTKMultiBlockDataSelector(const msvVTKMultiBlockDataSelector&); // Not implemented.
  void operator=(const msvVTKMultiBlockDataSelector&);               // Not implemented.

  msvVTKMultiBlockDataSelectorInternal* Internal;
};

#endif
