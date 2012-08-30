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

// MSVTK
#include "msvVTKXMLMultiblockLODReader.h"

// VTK includes

#include "vtkActor.h"
#include "vtkAlgorithmOutput.h"
#include "vtkAssignAttribute.h"
#include "vtkCompositePolyDataMapper2.h"
#include "vtkCollection.h"
#include "vtkMultiBlockDataSet.h"
#include "msvVTKMultiBlockDataSelector.h"
#include "vtkNew.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPolyDataReader.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkCompositeDataPipeline.h"
#include "vtkStringArray.h"
#include "vtkTestUtilities.h"

// STD includes
#include <cstdlib>
#include <iostream>
#include <string>

// -----------------------------------------------------------------------------
int msvVTKFileSeriesReaderPipelineTest(int argc, char* argv[])
{
  // Get the data test files
  /*const char* file0 =
    vtkTestUtilities::ExpandDataFileName(argc,argv,"Polydata00.vtk");
  const char* file1 =
    vtkTestUtilities::ExpandDataFileName(argc,argv,"Polydata00.vtk");*/

  const char* file = "/home/michael/HumanAnatomy/humanAnatomy.xml";

  /*--------------------------------------------------------------------------*/
  // CompositeLODReader
  /*--------------------------------------------------------------------------*/
  // Create the reader
  vtkNew<msvVTKXMLMultiblockLODReader> compositeMultiblocLODReader;
  compositeMultiblocLODReader->SetFileName(file);

  if (!compositeMultiblocLODReader->CanReadFile(file))
    {
    std::cerr << "Error: method CanReadFile must return true on: "
              << file << std::endl;
    return EXIT_FAILURE;
    }

  compositeMultiblocLODReader->GetMTime();

  if (strcmp(compositeMultiblocLODReader->GetFileName(), file) != 0)
    {
    std::cerr << "Error: GetFileName different than expected: " << std::endl
              << "Expected fileName: "
              << file << std::endl
              << "Filename retrived: "
              << compositeMultiblocLODReader->GetFileName()
              << std::endl;

    return EXIT_FAILURE;
    }

  //compositeMultiblocLODReader->Update();
  vtkMultiBlockDataSet* dataSet = vtkMultiBlockDataSet::SafeDownCast(
    compositeMultiblocLODReader->GetOutput());
  if (!dataSet)
    {
    std::cerr << "Error: vtkMultiBlockDataSet = null"
              << std::endl;
    return EXIT_FAILURE;
    }

  // Create instances of vtkDataObject for all outputsPorts
  vtkNew<vtkInformation> dataObjRequest;
  dataObjRequest->Set(vtkCompositeDataPipeline::REQUEST_DATA_OBJECT());
  compositeMultiblocLODReader->ProcessRequest(
    dataObjRequest.GetPointer(), 0,
    compositeMultiblocLODReader->GetExecutive()->GetOutputInformation());

  // Provide/Generate information on the output data
  vtkNew<vtkInformation> infoRequest1;
  infoRequest1->Set(vtkCompositeDataPipeline::REQUEST_INFORMATION());
  compositeMultiblocLODReader->ProcessRequest(
    infoRequest1.GetPointer(), 0,
    compositeMultiblocLODReader->GetExecutive()->GetOutputInformation());


  vtkNew<msvVTKMultiBlockDataSelector> mbSelector;
  mbSelector->SetInputConnection(compositeMultiblocLODReader->GetOutputPort());

  vtkNew<vtkCompositePolyDataMapper2> lodMapper;
  lodMapper->SetInputConnection(
    mbSelector->GetOutputPort());

  lodMapper->Update();
  mbSelector->SetDefaultLOD(0,0);

  return EXIT_SUCCESS;
}
