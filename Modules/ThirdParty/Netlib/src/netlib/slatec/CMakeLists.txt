add_library( itkNetlibSlatec
  # from SLATEC/FNLIB Used directly in ITK
        dbetai.c
        dgami.c
        dgamma.c
  #Used indirectly from above
    d1mach.c
    d9lgmc.c
    d9gmit.c
    d9lgic.c
    d9lgit.c
    dcsevl.c
    dgamit.c
    dgamlm.c
    dgamr.c
    dlbeta.c
    dlgams.c
    dlngam.c
    dlnrel.c
    initds.c
    xermsg.c
    d_int.c
    d_mod.c
 )

generate_export_header(itkNetlibSlatec
          BASE_NAME netlibslatec
          INCLUDE_GUARD_NAME __netlibslatec_export_h__
)

# Add include directories for both source and build trees
target_include_directories(itkNetlibSlatec
        PUBLIC
        # nothing here $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # your own headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>                         # generated export header
        # nothing to install $<INSTALL_INTERFACE:include>                      # where they'll live after install
)

if(ITK_USE_SYSTEM_VXL)
  target_link_libraries( itkNetlibSlatec v3p_netlib netlib)
else()
  target_link_libraries( itkNetlibSlatec itkv3p_netlib )
endif()

if(ITK_LIBRARY_PROPERTIES)
  set_target_properties(itkNetlibSlatec PROPERTIES ${ITK_LIBRARY_PROPERTIES})
endif()

install(TARGETS itkNetlibSlatec
  EXPORT ${ITK3P_INSTALL_EXPORT_NAME}
  RUNTIME DESTINATION ${ITK3P_INSTALL_RUNTIME_DIR} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${ITK3P_INSTALL_LIBRARY_DIR} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${ITK3P_INSTALL_ARCHIVE_DIR} COMPONENT Development)

# NOTE: netlibslatec_export.h is only used during building of this library
#       and does not need to be made public.
#       There is no public header, each use of these functions
#       explicitly defines the public interface in the cxx files
#       that use these methods
#install(FILES
# netlibslatec_export.h
# ${PROJECT_BINARY_DIR}/somelib_export.h
# DESTINATION ${ITK3P_INCLUDE_INSTALL_DIR}
#)
