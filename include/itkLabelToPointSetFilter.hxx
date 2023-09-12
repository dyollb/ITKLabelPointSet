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
#ifndef itkLabelToPointSetFilter_hxx
#define itkLabelToPointSetFilter_hxx

#include "itkLabelToPointSetFilter.h"

#include "itkImageRegionConstIterator.h"
#include "itkProgressReporter.h"

namespace itk
{

template <typename TInputImage, typename TOutputMesh>
LabelToPointSetFilter<TInputImage, TOutputMesh>::LabelToPointSetFilter()
{
  // Modify superclass default values, can be overridden by subclasses
  this->SetNumberOfRequiredInputs(1);

  PointDataContainerPointer pointData = PointDataContainer::New();

  OutputMeshPointer mesh = this->GetOutput();

  mesh->SetPointData(pointData);
}

template <typename TInputImage, typename TOutputMesh>
void
LabelToPointSetFilter<TInputImage, TOutputMesh>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

template <typename TInputImage, typename TOutputMesh>
void
LabelToPointSetFilter<TInputImage, TOutputMesh>::SetInput(const InputImageType * inputImage)
{
  // This const_cast is needed due to the lack of
  // const-correctness in the ProcessObject.
  this->SetNthInput(0, const_cast<InputImageType *>(inputImage));
}

template <typename TInputImage, typename TOutputMesh>
void
LabelToPointSetFilter<TInputImage, TOutputMesh>::GenerateOutputInformation()
{}

template <typename TInputImage, typename TOutputMesh>
void
LabelToPointSetFilter<TInputImage, TOutputMesh>::GenerateData()
{
  OutputMeshPointer      mesh = this->GetOutput();
  InputImageConstPointer image = this->GetInput(0);

  PointsContainerPointer    points = PointsContainer::New();
  PointDataContainerPointer pointData = PointDataContainer::New();

  auto             region = image->GetBufferedRegion();
  auto             numberOfPixels = region.GetNumberOfPixels();
  ProgressReporter progress(this, 0, static_cast<SizeValueType>(numberOfPixels));

  PointType point;

  ImageRegionConstIterator<TInputImage> it(image, region);
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
  {
    if (it.Get() != 0)
    {
      image->TransformIndexToPhysicalPoint(it.GetIndex(), point);
      points->push_back(point);
      pointData->push_back(it.Get());
    }
    progress.CompletedPixel();
  }

  mesh->SetPoints(points);
  mesh->SetPointData(pointData);

  // This indicates that the current BufferedRegion is equal to the
  // requested region. This action prevents useless rexecutions of
  // the pipeline.
  mesh->SetBufferedRegion(mesh->GetRequestedRegion());
}

} // end namespace itk

#endif // itkLabelToPointSetFilter_hxx
