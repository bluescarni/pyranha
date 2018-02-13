// Copyright 2018 Francesco Biscani (bluescarni@gmail.com)
//
// This file is part of the pyranha library.
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <mp++/config.hpp>
#include <mp++/extra/pybind11.hpp>

#include <piranha/integer.hpp>
#include <piranha/math/binomial.hpp>
#include <piranha/math/cos.hpp>
#include <piranha/math/sin.hpp>
#include <piranha/rational.hpp>
#if defined(MPPP_WITH_MPFR)
#include <piranha/real.hpp>
#endif

#include <pybind11/pybind11.h>

#include "docstrings.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

using namespace piranha;
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

    // Expose mathematical functions with numerical arguments.
    // Binomial coefficient.
    m.def("binomial", &piranha::binomial<const integer &, const integer &>, pyranha_binomial_docstring().c_str(), "x"_a,
          "y"_a);
    m.def("binomial", &piranha::binomial<const rational &, const integer &>, "x"_a, "y"_a);

    // Sine.
    m.def("sin", &piranha::sin<const double &>, pyranha_sin_docstring().c_str(), "x"_a);
    m.def("sin", &piranha::sin<const integer &>, "x"_a);
    m.def("sin", &piranha::sin<const rational &>, "x"_a);
#if defined(MPPP_WITH_MPFR)
    m.def("sin", &piranha::sin<const real &>, "x"_a);
#endif

    // Cosine.
    m.def("cos", &piranha::cos<const double &>, pyranha_cos_docstring().c_str(), "x"_a);
    m.def("cos", &piranha::cos<const integer &>, "x"_a);
    m.def("cos", &piranha::cos<const rational &>, "x"_a);
#if defined(MPPP_WITH_MPFR)
    m.def("cos", &piranha::cos<const real &>, "x"_a);
#endif
}
