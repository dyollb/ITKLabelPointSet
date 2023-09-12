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
#ifndef itkLabelToPointSetFilter_h
#define itkLabelToPointSetFilter_h

#include "itkImageToMeshFilter.h"

namespace itk
{

/** \class LabelToPointSetFilter
 *
 * \brief Filters a image by iterating over its pixels.
 *
 * Filters a image by iterating over its pixels in a multi-threaded way
 * and {to be completed by the developer}.
 *
 * \ingroup LabelPointSet
 *
 */
template <typename TInputImage, typename TOutputMesh>
class LabelToPointSetFilter : public ImageToMeshFilter<TInputImage, TOutputMesh>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(LabelToPointSetFilter);

  /** Standard class aliases. */
  using Self = LabelToPointSetFilter<TInputImage, TOutputMesh>;
  using Superclass = ImageToMeshFilter<TInputImage, TOutputMesh>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Standard New macro. */
  itkNewMacro(Self);

  /** Run-time type information. */
  itkTypeMacro(LabelToPointSetFilter, ImageToMeshFilter);

  using InputImageType = TInputImage;
  using InputImageConstPointer = typename InputImageType::ConstPointer;
  using InputPixelType = typename InputImageType::PixelType;

  using OutputMeshType = TOutputMesh;
  using OutputMeshPointer = typename OutputMeshType::Pointer;
  using PointType = typename OutputMeshType::PointType;
  using PointsContainer = typename OutputMeshType::PointsContainer;
  using PointsContainerPointer = typename PointsContainer::Pointer;
  using PointDataContainer = typename OutputMeshType::PointDataContainer;
  using PointDataContainerPointer = typename PointDataContainer::Pointer;

  /** Image dimension. */
  static constexpr unsigned int ImageDimension = TInputImage::ImageDimension;

  /** The dimension of the output mesh. */
  static constexpr unsigned int PointDimension = TOutputMesh::PointDimension;

  /** accept the input image */
  using Superclass::SetInput;
  void
  SetInput(const InputImageType * inputImage);

protected:
  LabelToPointSetFilter();
  ~LabelToPointSetFilter() override = default;

  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  /** Some type alias associated with the output mesh. */
  void
  GenerateData() override;

  /** Some type alias associated with the output mesh. */
  void
  GenerateOutputInformation() override;

private:
#ifdef ITK_USE_CONCEPT_CHECKING
  // Add concept checking such as
  // itkConceptMacro( FloatingPointPixel, ( itk::Concept::IsFloatingPoint< typename InputImageType::PixelType > ) );
#endif
};
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkLabelToPointSetFilter.hxx"
#endif

#endif // itkLabelToPointSetFilter
