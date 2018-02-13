// Copyright 2018 Francesco Biscani (bluescarni@gmail.com)
//
// This file is part of the pyranha library.
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <mp++/config.hpp>

#include <piranha/integer.hpp>
#include <piranha/math/binomial.hpp>
#include <piranha/math/cos.hpp>
#include <piranha/math/sin.hpp>
#include <piranha/rational.hpp>
#if defined(MPPP_WITH_MPFR)
#include <piranha/real.hpp>
#endif

#include <pybind11/pybind11.h>

#include "custom_type_casters.hpp"
#include "docstrings.hpp"
#include "expose_math.hpp"

namespace pyranha
{

void expose_math(pybind11::module &m)
{
    // Handy shortcuts.
    namespace py = pybind11;
    using namespace piranha;
    using namespace py::literals;

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
}