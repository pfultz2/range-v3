range-v3
========

Range library for C++11/14/17. This code is the basis of [a formal proposal](https://ericniebler.github.io/std/wg21/D4128.html) to add range support to the C++ standard library.

**Development Status:** This code is fairly stable, well-tested, and suitable for casual use, although currently lacking documentation. No promise is made about support or long-term stability. This code *will* evolve without regard to backwards compatibility.

**Build status (on Travis-CI):** [![Build Status](https://travis-ci.org/ericniebler/range-v3.svg?branch=master)](https://travis-ci.org/ericniebler/range-v3)

License:
--------

Most of the source code in this project are mine, and those are under the Boost Software License. Parts are taken from Alex Stepanov's Elements of Programming, Howard Hinnant's libc++, and from the SGI STL. Please see the attached LICENSE file and the CREDITS file for the licensing and acknolwedgements.

Supported Compilers
-------------------

The code is known to work on the following compilers:

- clang 3.4.0
- GCC 4.9.0

About:
------

Why does C++ need another range library? Simply put, the existing solutions haven't kept up with the rapid evolution of C++. Range v3 is a library for the future C++. Not only does it work well with today's C++ -- move semantics, lambdas, automatically deduced types and all -- it also anticipates tomorrow's C++ with Concepts Lite.

Range v3 forms the basis of a proposal to add range support to the standard library ([N4128: Ranges for the Standard Library](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4128.html)). It also will be the reference implementation for an upcoming Technical Specification. These are the first steps toward turning ranges into an international standard.

Documentation:
--------------

Check out the (woefully incomplete) documentation [here](https://ericniebler.github.io/range-v3/).
