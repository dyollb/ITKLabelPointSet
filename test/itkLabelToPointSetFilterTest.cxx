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

#include "itkLabelToPointSetFilter.h"

#include "itkCommand.h"
#include "itkPointSet.h"
#include "itkMeshFileWriter.h"
#include "itkTestingMacros.h"

namespace
{
class ShowProgress : public itk::Command
{
public:
  itkNewMacro(ShowProgress);

  void
  Execute(itk::Object * caller, const itk::EventObject & event) override
  {
    Execute((const itk::Object *)caller, event);
  }

  void
  Execute(const itk::Object * caller, const itk::EventObject & event) override
  {
    if (!itk::ProgressEvent().CheckEvent(&event))
    {
      return;
    }
    const auto * processObject = dynamic_cast<const itk::ProcessObject *>(caller);
    if (!processObject)
    {
      return;
    }
    std::cout << " " << processObject->GetProgress();
  }
};
} // namespace

int
itkLabelToPointSetFilterTest(int argc, char * argv[])
{
  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned short;
  using ImageType = itk::Image<PixelType, Dimension>;

  using PointSetType = itk::PointSet<PixelType, Dimension>;

  using FilterType = itk::LabelToPointSetFilter<ImageType, PointSetType>;
  FilterType::Pointer filter = FilterType::New();

  ITK_EXERCISE_BASIC_OBJECT_METHODS(filter, LabelToPointSetFilter, ImageToMeshFilter);

  // Create input image to avoid test dependencies.
  ImageType::SizeType size;
  size.Fill(128);
  ImageType::Pointer image = ImageType::New();
  image->SetRegions(size);
  image->Allocate();
  image->FillBuffer(0);
  double spacing[] = { 1.1, 0.87 };
  image->SetSpacing(spacing);

  std::vector<ImageType::IndexType> ids = { { 0, 2 }, { 18, 19 }, { 25, 25 }, { 80, 45 } };
  for (size_t i = 0; i < ids.size(); ++i)
  {
    image->SetPixel(ids[i], static_cast<PixelType>(i + 1));
  }

  ShowProgress::Pointer showProgress = ShowProgress::New();
  filter->AddObserver(itk::ProgressEvent(), showProgress);
  filter->SetInput(image);

  ITK_TRY_EXPECT_NO_EXCEPTION(filter->Update());

  auto point_set = filter->GetOutput();
  auto points = point_set->GetPoints();
  auto data = point_set->GetPointData();

  size_t num_failures = 0;
  size_t k = 0;
  for (auto p : *points)
  {
    auto pixel_value = data->at(k++);
    auto index = ids.at(pixel_value - 1);
    auto p2 = image->TransformIndexToPhysicalPoint<float>(index);
    auto diff = p.EuclideanDistanceTo(p2);
    if (diff > 1e-6)
    {
      std::cerr << "Point with pixel value '" << pixel_value << "' has is incorrect position.\n";
      num_failures++;
    }
  }

  if (num_failures > 0)
  {
    std::cerr << "Test failed." << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Test finished." << std::endl;
  return EXIT_SUCCESS;
}
