# CMake minimum required version
cmake_minimum_required(VERSION 3.12)

# Find git
find_package(Git)

if(NOT Git_FOUND)
	message(FATAL_ERROR "Could not find 'git' tool for RP2040-HAT-C patching")
endif()

message("RP2040-HAT-C patch utils found")

set(RP2040_HAT_C_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(IOLIBRARY_DRIVER_SRC_DIR "${RP2040_HAT_C_SRC_DIR}/libraries/ioLibrary_Driver")
set(MBEDTLS_SRC_DIR "${RP2040_HAT_C_SRC_DIR}/libraries/mbedtls")
set(RP2040_HAT_C_PATCH_DIR "${RP2040_HAT_C_SRC_DIR}/patches")

if(EXISTS "${IOLIBRARY_DRIVER_SRC_DIR}/.git")
	message("cleaning ioLibrary_Driver...")
	execute_process(COMMAND ${GIT_EXECUTABLE} -C ${IOLIBRARY_DRIVER_SRC_DIR} clean -fdx)
	execute_process(COMMAND ${GIT_EXECUTABLE} -C ${IOLIBRARY_DRIVER_SRC_DIR} reset --hard)
	message("ioLibrary_Driver cleaned")
endif()

if(EXISTS "${MBEDTLS_SRC_DIR}/.git")
	message("cleaning mbedtls...")
	execute_process(COMMAND ${GIT_EXECUTABLE} -C ${MBEDTLS_SRC_DIR} clean -fdx)
	execute_process(COMMAND ${GIT_EXECUTABLE} -C ${MBEDTLS_SRC_DIR} reset --hard)
	message("mbedtls cleaned")
endif()

execute_process(COMMAND ${GIT_EXECUTABLE} -C ${RP2040_HAT_C_SRC_DIR} submodule update --init)

# ioLibrary_Driver patch
message("submodules ioLibrary_Driver initialised")

file(GLOB IOLIBRARY_DRIVER_PATCHES 
	"${RP2040_HAT_C_PATCH_DIR}/01_ethernet_chip.patch" 
	"${RP2040_HAT_C_PATCH_DIR}/02_ftp_client.patch"
	)

foreach(IOLIBRARY_DRIVER_PATCH IN LISTS IOLIBRARY_DRIVER_PATCHES)
	message("Running patch ${IOLIBRARY_DRIVER_PATCH}")
	execute_process(
		COMMAND ${GIT_EXECUTABLE} apply ${IOLIBRARY_DRIVER_PATCH}
		WORKING_DIRECTORY ${IOLIBRARY_DRIVER_SRC_DIR}
	)
endforeach()

# mbedtls patch
message("submodules mbedtls initialised")

file(GLOB MBEDTLS_PATCHES 
	"${RP2040_HAT_C_PATCH_DIR}/03_mbedtls_test_mode.patch"
	)

foreach(MBEDTLS_PATCH IN LISTS MBEDTLS_PATCHES)
	message("Running patch ${MBEDTLS_PATCH}")
	execute_process(
		COMMAND ${GIT_EXECUTABLE} apply --ignore-whitespace ${MBEDTLS_PATCH}
		WORKING_DIRECTORY ${MBEDTLS_SRC_DIR}
	)
endforeach()
