// Copyright 2018 Francesco Biscani (bluescarni@gmail.com)
//
// This file is part of the pyranha library.
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
The root pyranha module.
    )";
}

std::string pyranha_math_binomial_docstring()
{
    return R"(binomial(x, y)

        Binomial coefficient.

        This function computes the binomial coefficient :math:`{x \choose y}`. The implementation
        is a thin wrapper around piranha's :cpp:func:`piranha::binomial() <piranha::binomial()>`
        function.

        Currently, this function supports :py:class:`integer <int>` and
        :py:class:`rational <fractions.Fraction>` arguments.

        Args:
            x: the top argument
            y: the bottom argument

        Returns:
            :math:`{x \choose y}`

        Raises:
            unspecified: any exception thrown by :cpp:func:`piranha::binomial() <piranha::binomial()>`
            TypeError: any exception thrown by :cpp:func:`piranha::binomial() <piranha::binomial()>`
    )";
}

std::string pyranha_math_sin_docstring()
{
    return R"(sin(x)

        Sine.

        This function computes :math:`\sin\left(x\right)`. The implementation
        is a thin wrapper around piranha's :cpp:func:`piranha::sin() <piranha::sin()>`
        function.

        Currently, this function supports :py:class:`integer <int>`, :py:class:`floating-point <float>`,
        :py:class:`rational <fractions.Fraction>` and :py:class:`mpf <mpmath.ctx_mp_python.mpf>` arguments.

        Args:
            x (array-like object): the decision vector whose gradient will be computed
    )";
}
}
