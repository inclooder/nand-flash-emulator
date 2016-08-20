# install libs
install(TARGETS nfe DESTINATION nfe/lib)

# install headers
install(FILES ${PROJECT_SOURCE_DIR}/src/nfe.h DESTINATION nfe/include)

# cpack
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT "Inclooder")
include(CPack)
