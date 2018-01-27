#include <mp++/extra/pybind11.hpp>

#include <pybind11/pybind11.h>

PYBIND11_MODULE(pyranha, m)
{
    m.doc() = "The Python bindings for the Piranha computer algebra system.";
}
