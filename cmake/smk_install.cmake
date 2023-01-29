include(GNUInstallDirs)
install(TARGETS smk stbimage libnyquist libwavpack
    EXPORT smk-export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/smk DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)
configure_package_config_file(smk-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/smk-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/smk/cmake
  PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)
write_basic_package_version_file(
  smk-config-version.cmake
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/smk-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/smk
)
install(EXPORT smk-export
  FILE smk-config-version.cmake
  NAMESPACE smk::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/smk
)
