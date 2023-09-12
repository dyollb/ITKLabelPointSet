itk_module_test()

set(LabelPointSetTests
  itkLabelToPointSetFilterTest.cxx
  )

CreateTestDriver(LabelPointSet "${LabelPointSet-Test_LIBRARIES}" "${LabelPointSetTests}")

itk_add_test(NAME itkLabelToPointSetFilterTest
  COMMAND LabelPointSetTestDriver
    --compare
    DATA{Baseline/itkLabelToPointSetFilterTestOutput.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkLabelToPointSetFilterTestOutput.mha
  itkLabelToPointSetFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkLabelToPointSetFilterTestOutput.mha
  )
