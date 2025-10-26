
if(BUILD_SHARED_LIBS)
    if(NOT MSVC)
        # Override to force default visibility when building shared libraries
        # A more fine grained solution would be to explicitly export the
        # the required symbols.
        set_source_files_properties(lib/lbfgs.c PROPERTIES COMPILE_OPTIONS "-fvisibility=default")
    endif()
endif()
add_library(itklbfgs lib/lbfgs.c)
target_include_directories(itklbfgs PRIVATE include)

if(ITK_LIBRARY_PROPERTIES)
  set_target_properties(itklbfgs PROPERTIES ${ITK_LIBRARY_PROPERTIES})
endif()

if(UNIX)
  target_link_libraries(itklbfgs m)
endif()

install(TARGETS itklbfgs
  EXPORT ${ITK3P_INSTALL_EXPORT_NAME}
  RUNTIME DESTINATION ${ITK3P_INSTALL_RUNTIME_DIR} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${ITK3P_INSTALL_LIBRARY_DIR} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${ITK3P_INSTALL_ARCHIVE_DIR} COMPONENT Development)

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/lbfgs.h
  DESTINATION ${ITK3P_INSTALL_INCLUDE_DIR}/itklbfgs/include)
