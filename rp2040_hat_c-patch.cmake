# CMake minimum required version
cmake_minimum_required(VERSION 3.12)

# Find git
find_package(Git)

if(NOT Git_FOUND)
	message(FATAL_ERROR "Could not find 'git' tool for RP2040-HAT-C patching")
endif()

message("RP2040-HAT-C patch utils found")

set(RP2040_HAT_C_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(RP2040_HAT_C_SRC_DIR_USB "${CMAKE_CURRENT_SOURCE_DIR}/libraries/pico-sdk")
set(IOLIBRARY_DRIVER_SRC_DIR "${RP2040_HAT_C_SRC_DIR}/libraries/ioLibrary_Driver")
set(RP2040_HAT_C_PATCH_DIR "${RP2040_HAT_C_SRC_DIR}/patches")

if(EXISTS "${IOLIBRARY_DRIVER_SRC_DIR}/.git")
	message("cleaning ioLibrary_Driver...")
	execute_process(COMMAND ${GIT_EXECUTABLE} -C ${IOLIBRARY_DRIVER_SRC_DIR} clean -fdx)
	execute_process(COMMAND ${GIT_EXECUTABLE} -C ${IOLIBRARY_DRIVER_SRC_DIR} reset --hard)
	message("ioLibrary_Driver cleaned")
endif()

# pico-sdk
execute_process(COMMAND ${GIT_EXECUTABLE} -C ${RP2040_HAT_C_SRC_DIR} submodule update --init)

# pico-tiny-usb
execute_process(COMMAND ${GIT_EXECUTABLE} -C ${RP2040_HAT_C_SRC_DIR_USB} submodule update --init)


# ioLibrary_Driver patch
message("submodules ioLibrary_Driver initialised")

file(GLOB IOLIBRARY_DRIVER_PATCHES 
	"${RP2040_HAT_C_PATCH_DIR}/01_iolibrary_driver_ethernet_chip.patch" 
	"${RP2040_HAT_C_PATCH_DIR}/02_iolibrary_driver_ftp_client.patch"
	)

foreach(IOLIBRARY_DRIVER_PATCH IN LISTS IOLIBRARY_DRIVER_PATCHES)
	message("Running patch ${IOLIBRARY_DRIVER_PATCH}")
	execute_process(
		COMMAND ${GIT_EXECUTABLE} apply ${IOLIBRARY_DRIVER_PATCH}
		WORKING_DIRECTORY ${IOLIBRARY_DRIVER_SRC_DIR}
	)
endforeach()
