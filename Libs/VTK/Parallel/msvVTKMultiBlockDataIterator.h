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

// .NAME msvVTKMultiBlockDataIterator - subclass of vtkCompositeDataIterator
//  with API to get current level and dataset index.
// .SECTION Description

#ifndef __msvVTKMultiBlockDataIterator_h
#define __msvVTKMultiBlockDataIterator_h

// VTK_PARALLEL includes
#include "msvVTKParallelExport.h"

#include "vtkCompositeDataIterator.h"

class MSV_VTK_PARALLEL_EXPORT msvVTKMultiBlockDataIterator :
  public vtkCompositeDataIterator
{
public:
  static msvVTKMultiBlockDataIterator* New();
  vtkTypeMacro(msvVTKMultiBlockDataIterator, vtkCompositeDataIterator);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Returns the level for the current dataset.
  unsigned int GetCurrentLevel();

  // Description:
  // Returns the dataset index for the current data object. Valid only if the
  // current data is a leaf node i.e. no a composite dataset.
  unsigned int GetCurrentIndex();

protected:
  msvVTKMultiBlockDataIterator();
  ~msvVTKMultiBlockDataIterator();

private:
  msvVTKMultiBlockDataIterator(const msvVTKMultiBlockDataIterator&); // Not implemented.
  void operator=(const msvVTKMultiBlockDataIterator&);               // Not implemented.

};

#endif
