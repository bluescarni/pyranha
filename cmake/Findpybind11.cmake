if(pybind11_INCLUDE_DIR)
    # Already in cache, be silent
    set(pybind11_FIND_QUIETLY TRUE)
endif()

find_path(pybind11_INCLUDE_DIR NAMES pybind11/pybind11.h)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(pybind11 DEFAULT_MSG pybind11_INCLUDE_DIR)

mark_as_advanced(pybind11_INCLUDE_DIR)

if(pybind11_FOUND)
    message(STATUS "pybind11 found, creating the pybind11::pybind11 target.")
    add_library(pybind11::pybind11 INTERFACE IMPORTED)
    set_target_properties(pybind11::pybind11 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${pybind11_INCLUDE_DIR}")
endif()
