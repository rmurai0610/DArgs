cmake_minimum_required(VERSION 3.2)
project(DArgs VERSION 0.1 LANGUAGES C CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
  ${PROJECT_NAME} INTERFACE "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
                            "$<INSTALL_INTERFACE:include>")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(config_install_dir "share/${PROJECT_NAME}/cmake")
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Targets:
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  INCLUDES
  DESTINATION include)

install(
  EXPORT ${PROJECT_NAME}Targets
  NAMESPACE ${PROJECT_NAME_CAPS}::
  DESTINATION "${config_install_dir}")

install(
  DIRECTORY "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}"
  DESTINATION include
)

export(
  TARGETS ${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAME_CAPS}::
  FILE ${PROJECT_NAME}Targets.cmake)

export(PACKAGE ${PROJECT_NAME})


configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${generated_dir}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "${config_install_dir}"
)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
write_basic_package_version_file(
  "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
  ARCH_INDEPENDENT
)

# Config
install(
  FILES
    "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake"
    "${generated_dir}/${PROJECT_NAME}Config.cmake"
  DESTINATION "${config_install_dir}"
)
