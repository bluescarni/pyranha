// Copyright 2018 Francesco Biscani (bluescarni@gmail.com)
//
// This file is part of the mp++ library.
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <mp++/config.hpp>
#include <mp++/extra/pybind11.hpp>

#include <piranha/integer.hpp>
#include <piranha/math/binomial.hpp>
#include <piranha/rational.hpp>

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

    py::module math_m = m.def_submodule("math");

    math_m.doc() = pyranha_math_docstring().c_str();

    math_m.def("binomial", math::binomial<const integer &, const integer &>, pyranha_math_binomial_docstring().c_str(),
               "x"_a, "y"_a);
    math_m.def("binomial", math::binomial<const rational &, const integer &>, "x"_a, "y"_a);
}
