set(DOCUMENTATION "This module contains the base classes needed to implement
finite differences image filters. They include both sparse and dense finite
differences. Most of the classes in this module are abstract and therefore are
not intended to be instantiated by themselves.")

# If building this module with explicit template instantiation, the module will
# need to be built as a shared library, and its dependencies will need to be
# escalated from DEPENDS ## COMPILE_DEPENDS to DEPENDS.  These changes are needed to
# ensure template instantiations are linked and shared correctly.

itk_module(ITKFiniteDifference
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS ## COMPILE_DEPENDS
    ITKCommon
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
