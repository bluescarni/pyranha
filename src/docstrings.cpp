// Copyright 2018 Francesco Biscani (bluescarni@gmail.com)
//
// This file is part of the mp++ library.
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include "docstrings.hpp"

namespace pyranha
{

std::string pyranha_docstring()
{
    return R"(
        Pyranha
        -------

        .. currentmodule:: pyranha

        .. autosummary::

           :toctree: _generate

           math
    )";
}

std::string pyranha_math_docstring()
{
    return R"(
        Math
        ----

        .. currentmodule:: pyranha.math

        .. autosummary::

           :toctree: _generate

           binomial
    )";
}

std::string pyranha_math_binomial_docstring()
{
    return R"(binomial(x, y)

        Binomial coefficient.

        Args:
            x (array-like object): the decision vector whose gradient will be computed
            y (array-like object): the decision vector whose gradient will be computed
    )";
}
}
