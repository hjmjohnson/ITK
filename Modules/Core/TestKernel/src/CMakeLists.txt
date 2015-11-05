if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  file(GLOB ITK_TESTKERNEL_EXPLICIT_SOURCES "*Explicit.cxx")
else()
  set(ITK_TESTKERNEL_EXPLICIT_SOURCES "")
endif()

set(ITKTestKernel_SRCS
${ITK_TESTKERNEL_EXPLICIT_SOURCES}
)

### generating libraries
if(ITKTestKernel_SRCS)
  add_library( ITKTestKernel ${ITK_LIBRARY_BUILD_TYPE} ${ITKTestKernel_SRCS})
  itk_module_link_dependencies()
endif()

add_executable(itkTestDriver itkTestDriver.cxx)
#target_link_libraries(itkTestDriver LINK_PUBLIC ${ITKTestKernel_LIBRARIES})
target_link_libraries(itkTestDriver
  LINK_PRIVATE ${ITK_MODULE_ITKTestKernel_PRIVATE_DEPENDS}
  LINK_PUBLIC ${ITK_MODULE_ITKTestKernel_PUBLIC_DEPENDS})
itk_module_target_label(itkTestDriver)
itk_module_target_export(itkTestDriver)
itk_module_target_install(itkTestDriver)
