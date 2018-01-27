cmake_policy(SET CMP0048 NEW)

project(pyranha VERSION 0.11 LANGUAGES CXX C)

cmake_minimum_required(VERSION 3.3.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_CURRENT_SOURCE_DIR}/cmake/yacma")

message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "pyranha version: ${pyranha_VERSION}")

# Set default build type to "Release".
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
	FORCE)
endif()

include(YACMACompilerLinkerSettings)
include(YACMAPythonSetup)
include(CheckCXXCompilerFlag)

# Check Python version.
if(${PYTHON_VERSION_MAJOR} LESS 2 OR (${PYTHON_VERSION_MAJOR} EQUAL 2 AND ${PYTHON_VERSION_MINOR} LESS 7))
  message(FATAL_ERROR "The minimum supported Python version is 2.7.")
endif()

# Assemble the flags.
set(PYRANHA_CXX_FLAGS_DEBUG ${YACMA_CXX_FLAGS} ${YACMA_CXX_FLAGS_DEBUG})
set(PYRANHA_CXX_FLAGS_RELEASE ${YACMA_CXX_FLAGS})
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND YACMA_COMPILER_IS_CLANGXX)
  message(STATUS "Clang compiler on OSX detected, setting the standard library to 'libc++'.")
  list(APPEND PYRANHA_CXX_FLAGS_DEBUG "-stdlib=libc++")
  list(APPEND PYRANHA_CXX_FLAGS_RELEASE "-stdlib=libc++")
endif()
if(YACMA_COMPILER_IS_MSVC)
  # Disable the idiotic minmax macros on MSVC, some annoying warnings,
  # and enable the bigobj option.
  list(APPEND PYRANHA_CXX_FLAGS_DEBUG "-DNOMINMAX" "/wd4459" "/wd4127" "/bigobj")
  list(APPEND PYRANHA_CXX_FLAGS_RELEASE "-DNOMINMAX" "/wd4459" "/wd4127" "/bigobj")
endif()
if(YACMA_COMPILER_IS_INTELXX)
  # NOTE: on MSVC we use the push/pop pragmas, but they do not seem to work on Intel (the pragmas
  # in icc influence the behaviour at instantiation point, not at definition point).
  list(APPEND PYRANHA_CXX_FLAGS_DEBUG "-diag-disable" "3373,1682")
  list(APPEND PYRANHA_CXX_FLAGS_RELEASE "-diag-disable" "3373,1682")
endif()
if(MINGW)
  # In MinGW some tests generate big object files.
  list(APPEND PYRANHA_CXX_FLAGS_DEBUG "-Wa,-mbig-obj")
  list(APPEND PYRANHA_CXX_FLAGS_RELEASE "-Wa,-mbig-obj")
endif()

if(YACMA_COMPILER_IS_GNUCXX)
    # This is just a hackish way of detecting concepts, need to revisit once
    # more compilers support them.
    check_cxx_compiler_flag("-fconcepts" PYRANHA_COMPILER_SUPPORTS_CONCEPTS)
endif()

# Find mp++. The pybind11 integration is available since 0.6.
# NOTE: the mp++ dependency is brought in by piranha anyway,
# but let's play by the rules - we need to include the pybind11
# mp++ bits independently from piranha.
find_package(mp++ 0.6 REQUIRED)
list(APPEND PYRANHA_MANDATORY_LINK_TARGETS mp++::mp++)

# Find piranha. Let's keep the piranha and pyranha versions in sync
# for the time being.
find_package(piranha ${pyranha_VERSION} EXACT REQUIRED)
list(APPEND PYRANHA_MANDATORY_LINK_TARGETS Piranha::piranha)

# Find pybind11.
find_package(pybind11 REQUIRED)

YACMA_PYTHON_MODULE(pyranha src/pyranha.cpp)
target_link_libraries(pyranha PRIVATE ${PYRANHA_MANDATORY_LINK_TARGETS})
target_compile_options(pyranha PRIVATE "$<$<CONFIG:DEBUG>:${PYRANHA_CXX_FLAGS_DEBUG}>" "$<$<CONFIG:RELEASE>:${PYRANHA_CXX_FLAGS_RELEASE}>")
