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

std::string pyranha_run_test_suite_docstring()
{
    return R"(run_test_suite()

    Run pyranha's full test suite.

    Informative text output will be printed to screen during the execution of the
    test suite. In any test fails, a :py:class:`RuntimeError` exception will be raised.

    )";
}

std::string pyranha_binomial_docstring()
{
    return R"(binomial(x, y)

        Binomial coefficient.

        This function computes the binomial coefficient :math:`{x \choose y}`. The implementation
        is a thin wrapper around piranha's :cpp:func:`binomial() <piranha::binomial()>`
        function.

        This function currently supports the following argument types:

        * :py:class:`int`,
        * :py:class:`fractions.Fraction`.

        Args:
            x: the top argument
            y: the bottom argument

        Returns:
            :math:`{x \choose y}`

        Raises:
            TypeError: if the function arguments are incompatible with the exposed C++ overloads
            unspecified: any exception thrown by :cpp:func:`piranha::binomial() <piranha::binomial()>`

        Examples:
            >>> from fractions import Fraction as F
            >>> binomial(42, 2)
            861
            >>> binomial(-5, -10)
            -126
            >>> binomial(F(-5, 6), 3)
            Fraction(-935, 1296)
            >>> binomial(3.4, 5.6) # doctest: +IGNORE_EXCEPTION_DETAIL
            Traceback (most recent call last):
               ...
            TypeError: binomial(): incompatible function arguments

    )";
}

std::string pyranha_sin_docstring()
{
    return R"(sin(x)

        Sine.

        This function computes :math:`\sin\left(x\right)`. The implementation
        is a thin wrapper around piranha's :cpp:func:`sin() <piranha::sin()>`
        function.

        This function currently supports the following argument types:

        * :py:class:`int`,
        * :py:class:`fractions.Fraction`,
        * :py:class:`float`,
        * ``mpf``.

        Args:
            x: the sine argument

        Returns:
            :math:`\sin\left(x\right)`

        Raises:
            TypeError: if the function argument is incompatible with the exposed C++ overloads
            unspecified: any exception thrown by :cpp:func:`piranha::sin() <piranha::sin()>`

        Examples:
            >>> from fractions import Fraction as F
            >>> sin(1.1) # doctest: +ELLIPSIS
            0.89120...
            >>> sin(F(0, 1))
            Fraction(0, 1)
            >>> sin(14) # doctest: +IGNORE_EXCEPTION_DETAIL
            Traceback (most recent call last):
               ...
            ValueError: cannot compute the sine of the non-zero integer 14
            >>> sin("foo") # doctest: +IGNORE_EXCEPTION_DETAIL
            Traceback (most recent call last):
               ...
            TypeError: sin(): incompatible function arguments

    )";
}

std::string pyranha_cos_docstring()
{
    return R"(cos(x)

        Cosine.

        This function computes :math:`\cos\left(x\right)`. The implementation
        is a thin wrapper around piranha's :cpp:func:`cos() <piranha::cos()>`
        function.

        This function currently supports the following argument types:

        * :py:class:`int`,
        * :py:class:`fractions.Fraction`,
        * :py:class:`float`,
        * ``mpf``.

        Args:
            x: the cosine argument

        Returns:
            :math:`\cos\left(x\right)`

        Raises:
            TypeError: if the function argument is incompatible with the exposed C++ overloads
            unspecified: any exception thrown by :cpp:func:`piranha::cos() <piranha::cos()>`

        Examples:
            >>> from fractions import Fraction as F
            >>> cos(1.1) # doctest: +ELLIPSIS
            0.45359...
            >>> cos(F(0, 1))
            Fraction(1, 1)
            >>> cos(14) # doctest: +IGNORE_EXCEPTION_DETAIL
            Traceback (most recent call last):
               ...
            ValueError: cannot compute the cosine of the non-zero integer 14
            >>> cos("foo") # doctest: +IGNORE_EXCEPTION_DETAIL
            Traceback (most recent call last):
               ...
            TypeError: cos(): incompatible function arguments

    )";
}

std::string pyranha_is_zero_docstring()
{
    return R"(is_zero(x)

        Detect zero.

        This function returns ``True`` if *x* is equal to zero, ``False`` otherwise.
        The implementation is a thin wrapper around piranha's
        :cpp:func:`is_zero() <piranha::is_zero()>` function.

        This function currently supports the following argument types:

        * :py:class:`int`,
        * :py:class:`fractions.Fraction`,
        * :py:class:`float`,
        * ``mpf``.

        Args:
            x: the object that will be tested

        Returns:
            ``True`` if *x* is equal to zero, ``False`` otherwise

        Raises:
            TypeError: if the function argument is incompatible with the exposed C++ overloads
            unspecified: any exception thrown by :cpp:func:`piranha::is_zero() <piranha::is_zero()>`

        Examples:
            >>> from fractions import Fraction as F
            >>> is_zero(0.1)
            False
            >>> is_zero(F(0, 1))
            True
            >>> is_zero("foo") # doctest: +IGNORE_EXCEPTION_DETAIL
            Traceback (most recent call last):
               ...
            TypeError: is_zero(): incompatible function arguments

    )";
}

std::string pyranha_is_one_docstring()
{
    return R"(is_one(x)

        Detect one.

        This function returns ``True`` if *x* is equal to one, ``False`` otherwise.
        The implementation is a thin wrapper around piranha's
        :cpp:func:`is_one() <piranha::is_one()>` function.

        This function currently supports the following argument types:

        * :py:class:`int`,
        * :py:class:`fractions.Fraction`,
        * :py:class:`float`,
        * ``mpf``.

        Args:
            x: the object that will be tested

        Returns:
            ``True`` if *x* is equal to one, ``False`` otherwise

        Raises:
            TypeError: if the function argument is incompatible with the exposed C++ overloads
            unspecified: any exception thrown by :cpp:func:`piranha::is_one() <piranha::is_one()>`

        Examples:
            >>> from fractions import Fraction as F
            >>> is_one(0.1)
            False
            >>> is_one(F(1, 1))
            True
            >>> is_one("foo") # doctest: +IGNORE_EXCEPTION_DETAIL
            Traceback (most recent call last):
               ...
            TypeError: is_one(): incompatible function arguments

    )";
}
}
