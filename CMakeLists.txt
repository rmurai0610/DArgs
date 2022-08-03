cmake_minimum_required(VERSION 3.2)
project(DArgs LANGUAGES C CXX)

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

export(
  TARGETS ${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAME_CAPS}::
  FILE ${PROJECT_NAME}Targets.cmake)

export(PACKAGE ${PROJECT_NAME})
