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

#include "msvVTKMultiBlockDataIterator.h"

#include "vtkCompositeDataSetInternals.h"
#include "vtkObjectFactory.h"

vtkStandardNewMacro(msvVTKMultiBlockDataIterator);

//------------------------------------------------------------------------------
msvVTKMultiBlockDataIterator::msvVTKMultiBlockDataIterator()
{
}

//------------------------------------------------------------------------------
msvVTKMultiBlockDataIterator::~msvVTKMultiBlockDataIterator()
{
}

//------------------------------------------------------------------------------
unsigned int msvVTKMultiBlockDataIterator::GetCurrentLevel()
{
  if (this->IsDoneWithTraversal())
    {
    vtkErrorMacro("IsDoneWithTraversal is true.");
    return 0;
    }

  vtkCompositeDataSetIndex index = this->Superclass::GetCurrentIndex();
  return index[0];
}

//------------------------------------------------------------------------------
unsigned int msvVTKMultiBlockDataIterator::GetCurrentIndex()
{
  if (this->IsDoneWithTraversal())
    {
    vtkErrorMacro("IsDoneWithTraversal is true.");
    return 0;
    }

  vtkCompositeDataSetIndex index = this->Superclass::GetCurrentIndex();
  if (index.size()==2)
    {
    return index[1];
    }
  return 0;
}

//------------------------------------------------------------------------------
void msvVTKMultiBlockDataIterator::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
