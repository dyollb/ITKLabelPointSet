itk_module_test()

set(LabelPointSetTests
  itkLabelToPointSetFilterTest.cxx
  )

CreateTestDriver(LabelPointSet "${LabelPointSet-Test_LIBRARIES}" "${LabelPointSetTests}")


itk_add_test(NAME itkLabelToPointSetFilterTest
  COMMAND LabelPointSetTestDriver itkLabelToPointSetFilterTest
  )
