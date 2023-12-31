# ITKLabelPointSet

[![Build Status](https://github.com/dyollb/ITKLabelPointSet/workflows/Build,%20test,%20package/badge.svg)](https://github.com/dyollb/ITKLabelPointSet/actions)
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://github.com/dyollb/ITKLabelPointSet/blob/main/LICENSE)
[![PyPI version](https://img.shields.io/pypi/v/itk-labelpointset.svg)](https://badge.fury.io/py/itk-labelpointset)
<img src="https://img.shields.io/pypi/dm/itk-labelpointset.svg?label=pypi%20downloads&logo=python&logoColor=green"/>
<img src="https://img.shields.io/badge/python-%203.7%20|%203.8%20|%203.9%20|%203.10%20|%203.11%20-3776ab.svg"/>

## Overview

This is a module for the Insight Toolkit ([ITK](https://github.com/InsightSoftwareConsortium/ITK)). The module includes a filter to extract a PointSet from a labeled image.
Additional filters and IO classes may be added in future versions to support pointset registration workflows.

```python
    import itk

    labels = itk.imread('path/to/labelmap.mha').astype(itk.US)
    D = labels.ndim

    ImageType = type(labels)
    PointSetType = itk.PointSet[itk.US, D]

    extractor = itk.LabelToPointSetFilter[ImageType, PointSetType].New()
    extractor.SetInput(labels)
    extractor.Update()
    point_set = extractor.GetOutput()

    data = point_set.GetPointData()
    for i in range(point_set.GetNumberOfPoints()):
      print(f"{i}: {point_set.GetPoint(i)}, {data.GetElement(i)}")
```

## Installation

To install the binary Python packages:

```shell
  python -m pip install itk-labelpointset
```
