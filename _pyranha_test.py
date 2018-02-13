
# Copyright 2018 Francesco Biscani (bluescarni@gmail.com)
#
# This file is part of the pyranha library.
#
# This Source Code Form is subject to the terms of the Mozilla
# Public License v. 2.0. If a copy of the MPL was not distributed
# with this file, You can obtain one at http:#mozilla.org/MPL/2.0/.

from __future__ import absolute_import as _ai

import unittest as _ut


class math_test_case(_ut.TestCase):
    def runTest(self):
        # import math
        # from .math import cos as pcos, sin as psin
        # from .types import polynomial, k_monomial, double
        # pt = polynomial[double, k_monomial]()
        # self.assertAlmostEqual(math.cos(3), pcos(pt(3)).list[0][0])
        # self.assertAlmostEqual(math.cos(2.456), pcos(pt(2.456)).list[0][0])
        # self.assertAlmostEqual(math.sin(3), psin(pt(3)).list[0][0])
        # self.assertAlmostEqual(math.sin(-2.456), psin(pt(-2.456)).list[0][0])
        self.binomialTest()
        self.sincosTest()

    def binomialTest(self):
        from pyranha import binomial
        from fractions import Fraction as F
        self.assertEqual(type(binomial(5, 4)), int)
        self.assertEqual(binomial(-5, 4), 70)
        self.assertEqual(binomial(x=-5, y=4), 70)
        self.assertEqual(binomial(y=4, x=-5), 70)
        self.assertEqual(binomial(F(7, 3), 4), F(-7, 243))
        self.assertEqual(binomial(x=F(7, 3), y=4), F(-7, 243))
        self.assertEqual(binomial(y=4, x=F(7, 3)), F(-7, 243))
        self.assertEqual(type(binomial(F(7, 3), 4)), F)
        self.assertEqual(binomial(F(7, -3), 4), F(1820, 243))
        with self.assertRaises(TypeError) as cm:
            binomial(F(7, -3), F(4, 5))
        self.assertTrue('incompatible function arguments' in str(cm.exception))
        with self.assertRaises(TypeError) as cm:
            binomial(x=F(7, 3), a=4)
        self.assertTrue('incompatible function arguments' in str(cm.exception))

    def sincosTest(self):
        from fractions import Fraction as F
        from pyranha import sin, cos, _with_mpfr
        from math import sin as psin, cos as pcos
        # Check the return types.
        self.assertEqual(type(cos(0)), int)
        self.assertEqual(type(sin(0)), int)
        self.assertEqual(type(cos(F(0))), F)
        self.assertEqual(type(sin(F(0))), F)
        self.assertEqual(type(cos(1.)), float)
        self.assertEqual(type(sin(1.)), float)
        with self.assertRaises(TypeError) as cm:
            cos("")
        self.assertTrue('incompatible function arguments' in str(cm.exception))
        with self.assertRaises(TypeError) as cm:
            sin("")
        self.assertTrue('incompatible function arguments' in str(cm.exception))
        with self.assertRaises(ValueError) as cm:
            cos(5)
        self.assertTrue(
            'cannot compute the cosine of the non-zero integer' in str(cm.exception))
        with self.assertRaises(ValueError) as cm:
            sin(5)
        self.assertTrue(
            'cannot compute the sine of the non-zero integer' in str(cm.exception))
        # NOTE: according to
        # https://docs.python.org/3/library/math.html
        # the CPython math functions are wrappers around the corresponding
        # C functions. The results should thus be roughly the same.
        self.assertAlmostEqual(cos(3.), pcos(3.))
        self.assertAlmostEqual(cos(x=3.), pcos(3.))
        self.assertAlmostEqual(cos(3.1234), pcos(3.1234))
        self.assertAlmostEqual(sin(3.), psin(3.))
        self.assertAlmostEqual(sin(x=3.), psin(3.))
        self.assertAlmostEqual(sin(3.1234), psin(3.1234))
        with self.assertRaises(TypeError) as cm:
            cos(a=5)
        self.assertTrue('incompatible function arguments' in str(cm.exception))
        with self.assertRaises(TypeError) as cm:
            sin(a=5)
        self.assertTrue('incompatible function arguments' in str(cm.exception))
        if not _with_mpfr:
            return
        try:
            from mpmath import mpf, workdps, cos as mp_cos, sin as mp_sin
        except ImportError:
            return
        with workdps(100):
            self.assertEqual(type(cos(mpf(1))), mpf)
            self.assertEqual(type(sin(mpf(1))), mpf)
            self.assertEqual(cos(mpf(1)), mp_cos(1))
            self.assertEqual(sin(mpf(1)), mp_sin(1))


class doctests_test_case(_ut.TestCase):
    def runTest(self):
        import doctest
        import pyranha
        try:
            doctest.testmod(pyranha, raise_on_error=True)
        except Exception as e:
            self.fail(str(e))


def run_test_suite():
    retval = 0
    suite = _ut.TestLoader().loadTestsFromTestCase(math_test_case)
    suite.addTest(doctests_test_case())
    test_result = _ut.TextTestRunner(verbosity=2).run(suite)
    if len(test_result.failures) > 0 or len(test_result.errors) > 0:
        retval = 1
    if retval != 0:
        raise RuntimeError('One or more tests failed.')
