# CMake minimum required version
cmake_minimum_required(VERSION 3.12)

# Find git
find_package(Git)

if(NOT Git_FOUND)
	message(FATAL_ERROR "Could not find 'git' tool for RP2040-HAT-C ioLibrary_Driver patching")
endif()

message("RP2040-HAT-C patch utils found")

set(RP2040_HAT_C_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(IOLIBRARY_DRIVER_SRC_DIR "${RP2040_HAT_C_SRC_DIR}/libraries/ioLibrary_Driver")
set(RP2040_HAT_C_PATCH_DIR "${RP2040_HAT_C_SRC_DIR}/patches")

if(EXISTS "${IOLIBRARY_DRIVER_SRC_DIR}/.git")
	message("cleaning ioLibrary_Driver...")
	execute_process(COMMAND ${GIT_EXECUTABLE} -C ${IOLIBRARY_DRIVER_SRC_DIR} clean -fdx)
	execute_process(COMMAND ${GIT_EXECUTABLE} -C ${IOLIBRARY_DRIVER_SRC_DIR} reset --hard)
	message("ioLibrary_Driver cleaned")
endif()

execute_process(COMMAND ${GIT_EXECUTABLE} -C ${RP2040_HAT_C_SRC_DIR} submodule update --init)

message("submodules initialised")

file(GLOB PATCHES "${RP2040_HAT_C_PATCH_DIR}/*.patch")

foreach(PATCH IN LISTS PATCHES)
	message("Running patch ${PATCH}")
	execute_process(
		COMMAND ${GIT_EXECUTABLE} apply ${PATCH}
		WORKING_DIRECTORY ${IOLIBRARY_DRIVER_SRC_DIR}
	)
endforeach()
