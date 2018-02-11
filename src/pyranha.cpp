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

    py::options options;
    options.disable_function_signatures();

    m.doc() = pyranha_docstring().c_str();

    m.def("binomial", &piranha::binomial<const integer &, const integer &>, pyranha_math_binomial_docstring().c_str(),
          "x"_a, "y"_a);
    m.def("binomial", &piranha::binomial<const rational &, const integer &>, "x"_a, "y"_a);

    m.def("sin", &piranha::sin<const double &>, pyranha_math_sin_docstring().c_str(), "x"_a);
    m.def("sin", &piranha::sin<const integer &>, "x"_a);
    m.def("sin", &piranha::sin<const rational &>, "x"_a);
#if defined(MPPP_WITH_MPFR)
    m.def("sin", &piranha::sin<const real &>, "x"_a);
#endif
}
