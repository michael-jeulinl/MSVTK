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
#include "msvVTKMultiBlockDataSelector.h"

#include "vtkCompositeDataIterator.h"
#include "vtkCompositeDataPipeline.h"
#include "vtkCompositeDataSetInternals.h"
#include "vtkDataSet.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "msvVTKMultiBlockDataIterator.h"
#include "vtkMultiBlockDataSet.h"
#include "vtkNew.h"
#include "vtkObjectFactory.h"
#include "vtkSmartPointer.h"
#include "vtkStreamingDemandDrivenPipeline.h"

#include <list>
#include <vector>

vtkStandardNewMacro(msvVTKMultiBlockDataSelector);

//------------------------------------------------------------------------------
class msvVTKMultiBlockDataSelectorInternal
{
public:
  msvVTKMultiBlockDataSelectorInternal();
  ~msvVTKMultiBlockDataSelectorInternal();

  void GetIndicesFromDefaultLOD(vtkCompositeDataSet* data,
                                unsigned int lod,
                                std::vector<int>& indices);

  unsigned int CurrentFlatIndex;
};

//------------------------------------------------------------------------------
// msvVTKXMLMultiblockLODReaderInternal methods

//------------------------------------------------------------------------------
void msvVTKMultiBlockDataSelectorInternal::
GetIndicesFromDefaultLOD(vtkCompositeDataSet* data,
                         unsigned int lod,
                         std::vector<int>& indices)
{
  int currentDataLevel = 2;
  if(!data || currentDataLevel == 1)
    {
    return;
    }

  // Will contains the blocks just above the LOD ones.
  std::list<vtkCompositeDataSet*> fatherDataSets;

  vtkSmartPointer<vtkCompositeDataIterator> it;
  it.TakeReference(data->NewIterator());
  it->SetSkipEmptyNodes(0);
  it->SetVisitOnlyLeaves(0);
  it->SetTraverseSubTree(1);

  // for level

  for(it->InitTraversal(); !it->IsDoneWithTraversal(); it->GoToNextItem())
    {
    fatherDataSets.push_back(it->GetDataSet());
    indices.push_back(it->GetCurrentFlatIndex());

    vtkCompositeDataSetIndex index = it->GetCurrentIndex();
    std::cout << it->GetCurrentFlatIndex()
              << " - " << index[1] << std::endl;
    }

  int level = 1;
  while(level < currentDataLevel-1)
    {
      // For every blocks :

      // As long as we are before the father level we add the indices
      // When we will be at the father level, we keep the composite data to set
      // the indices given the LOD choosen as well as their own indices
      if(level == (currentDataLevel-1))
        {
        level = level;
        //fatherDataSets.push_back(*it);
        }

      else
        {
        indices.push_back(it->GetCurrentFlatIndex());
        }

      ++level;
    }


  for(std::list<vtkCompositeDataSet*>::iterator fatherIt = fatherDataSets.begin();
      fatherIt != fatherDataSets.end(); ++ fatherIt)
    {
    // Clamp LOD
      int a;
    //fatherIt->
    }

}

//------------------------------------------------------------------------------
// msvVTKXMLMultiblockLODReader methods

//------------------------------------------------------------------------------
msvVTKMultiBlockDataSelector::msvVTKMultiBlockDataSelector()
{
}

//------------------------------------------------------------------------------
msvVTKMultiBlockDataSelector::~msvVTKMultiBlockDataSelector()
{
}

//------------------------------------------------------------------------------
int msvVTKMultiBlockDataSelector::SetDefaultLOD(int port, unsigned int lod)
{
  return
    this->SetDefaultLOD(this->GetExecutive()->GetOutputInformation(port), lod);
}

//------------------------------------------------------------------------------
int msvVTKMultiBlockDataSelector::SetDefaultLOD(vtkInformation *inInfo,
                                                unsigned int lod)
{
  vtkCompositeDataSet* multiblock = vtkCompositeDataSet::SafeDownCast(
    this->GetInputDataObject(0, 0));

  if(!inInfo || !multiblock)
    {
    vtkGenericWarningMacro("SetDefaultLOD on invalid output");
    return 0;
    }

  int modified = 0;
  std::vector<int> updateIndices;

  // Fill the indices needed
  this->Internal->GetIndicesFromDefaultLOD(multiblock, lod, updateIndices);


  // Check the info
  // If the indices [updateIndices] are the same as the COMPOSITE_INDICES
  // Then do not make it as a change.

  return modified;
}


//------------------------------------------------------------------------------
int msvVTKMultiBlockDataSelector::
RequestUpdateExtent(vtkInformation*,
                    vtkInformationVector** inputVector,
                    vtkInformationVector*)
{
  vtkDebugMacro("RequestUpdateExtent");

  // Check if metadata are passed downstream
  vtkInformation * inInfo = inputVector[0]->GetInformationObject(0);

  /**
    Use appropriate information to make the indices selection.
    **/

  std::vector<int> blocksToLoad;
  blocksToLoad.push_back(2);
  blocksToLoad.push_back(4);
  blocksToLoad.push_back(6);
  blocksToLoad.push_back(8);
  blocksToLoad.push_back(10);

  inInfo->Set(vtkCompositeDataPipeline::UPDATE_COMPOSITE_INDICES(),
              &blocksToLoad[0], static_cast<int>(blocksToLoad.size()));

  return 1;
}

//------------------------------------------------------------------------------
void msvVTKMultiBlockDataSelector::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
