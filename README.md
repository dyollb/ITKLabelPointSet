# ITKLabelPointSet

[![Build Status](https://github.com/dyollb/ITKLabelPointSet/workflows/Build,%20test,%20package/badge.svg)](https://github.com/dyollb/ITKLabelPointSet/actions)
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://github.com/dyollb/ITKLabelPointSet/blob/main/LICENSE)
[![PyPI version](https://img.shields.io/pypi/v/itk-labelpointset.svg)](https://badge.fury.io/py/itk-labelpointset)
<img src="https://img.shields.io/pypi/dm/itk-labelpointset.svg?label=pypi%20downloads&logo=python&logoColor=green"/>
<img src="https://img.shields.io/badge/python-%203.7%20|%203.8%20|%203.9%20|%203.10%20|%203.11%20-3776ab.svg"/>

## Overview

This is a module for the Insight Toolkit ([ITK](https://github.com/InsightSoftwareConsortium/ITK)). The module includes a filter to extract a PointSet from a labeled image.

```python
    import itk
    skull_mask = itk.imread('path/to/skull_with_holes.mha').astype(itk.US)

    ImageType = type(skull_mask)
    MaskType = itk.Image[itk.UC, 3]

    top_control = itk.FixTopologyCarveOutside[ImageType, ImageType, MaskType].New()
    top_control.SetInput(skull_mask)
    top_control.SetRadius(5)
    top_control.Update()
    skull_mask_closed = top_control.GetOutput()

    itk.imwrite(skull_mask_closed, 'skull_mask_closed.mha')
```

## Installation

To install the binary Python packages:

```shell
  python -m pip install itk-labelpointset
```
