// Copyright 2018 Francesco Biscani (bluescarni@gmail.com)
//
// This file is part of the pyranha library.
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iterator>
#include <sstream>
#include <string>

#include <boost/container/container_fwd.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include <mp++/config.hpp>

#include <piranha/symbol_utils.hpp>

#include <pybind11/pybind11.h>

// NOTE: let's make sure this is always included first.
#include "custom_type_casters.hpp"

#include "docstrings.hpp"
#include "expose_math.hpp"

namespace py = pybind11;

using namespace pyranha;

PYBIND11_MODULE(pyranha, m)
{
    mppp_pybind11::init();

    // Disable function signatures, we will provide
    // our own in the docstrings.
    py::options options;
    options.disable_function_signatures();

    // Main module docstring.
    m.doc() = pyranha_docstring().c_str();

    // Detect the presence of optional piranha/mp++
    // features. Keep them as private members for now.
    m.attr("_with_mpfr") =
#if defined(MPPP_WITH_MPFR)
        true
#else
        false
#endif
        ;

    // Wrapper for running the test suite.
    m.def("run_test_suite", []() { py::module::import("_pyranha_test").attr("run_test_suite")(); },
          pyranha_run_test_suite_docstring().c_str());

    py::class_<piranha::symbol_fset>(m, "symbol_fset")
        .def(py::init<>())
        .def(py::init([](py::object o) -> piranha::symbol_fset {
            // NOTE: let's just avoid lambdas here, as I am not 100% sure that
            // Boost's iterator library plays nice with them.
            struct make_ss_transform {
                std::string operator()(const py::handle &h) const
                {
                    return h.cast<std::string>();
                }
            };
            return piranha::symbol_fset{boost::make_transform_iterator(std::begin(o), make_ss_transform{}),
                                        boost::make_transform_iterator(std::end(o), make_ss_transform{})};
        }))
        .def("__repr__",
             [](const piranha::symbol_fset &s) -> std::string {
                 std::ostringstream oss;
                 oss << "{";
                 for (auto it = std::begin(s); it != std::end(s);) {
                     oss << "'" << *it << "'";
                     if (++it != std::end(s)) {
                         oss << ", ";
                     }
                 }
                 oss << "}";
                 return oss.str();
             })
        .def("clear", &piranha::symbol_fset::clear)
        .def("__len__", &piranha::symbol_fset::size)
        .def("__iter__", [](piranha::symbol_fset &s) { return py::make_iterator(s.begin(), s.end()); },
             py::keep_alive<0, 1>());

    // Expose mathematical functions with numerical arguments.
    expose_math(m);
}
