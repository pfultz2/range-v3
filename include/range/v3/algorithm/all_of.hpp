// Range v3 library
//
//  Copyright Andrew Sutton 2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//
#ifndef RANGES_V3_ALGORITHM_ALL_OF_HPP
#define RANGES_V3_ALGORITHM_ALL_OF_HPP

#include <utility>
#include <range/v3/range_fwd.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/range_concepts.hpp>
#include <range/v3/range_traits.hpp>
#include <range/v3/utility/functional.hpp>
#include <range/v3/utility/iterator_concepts.hpp>
#include <range/v3/utility/iterator_traits.hpp>
#include <range/v3/utility/range_algorithm.hpp>

namespace ranges
{
    inline namespace v3
    {
        struct all_of_fn
        {
            template<typename I, typename S, typename F, typename P = ident,
                typename V = iterator_value_t<I>,
                typename X = concepts::Invokable::result_t<P, V>,
                CONCEPT_REQUIRES_(
                    InputIterator<I>() && IteratorRange<I, S>() &&
                    Invokable<P, V>() &&
                    InvokablePredicate<F, X>()
                )>
            bool
            operator()(I first, S last, F pred, P proj = P{}) const
            {
                auto &&ipred = invokable(pred);
                auto &&iproj = invokable(proj);
                for(; first != last; ++first)
                    if(!ipred(iproj(*first)))
                        break;
                return first == last;
            }

            template<typename Rng, typename F, typename P = ident,
                typename I = range_iterator_t<Rng>,
                typename V = iterator_value_t<I>,
                typename X = concepts::Invokable::result_t<P, V>,
                CONCEPT_REQUIRES_(
                    InputIterable<Rng>() &&
                    Invokable<P, V>() &&
                    InvokablePredicate<F, X>()
                )>
            bool
            operator()(Rng &&rng, F pred, P proj = P{}) const
            {
                return (*this)(begin(rng), end(rng), std::move(pred), std::move(proj));
            }
        };

        RANGES_CONSTEXPR range_algorithm<all_of_fn> all_of {};

    } // inline namespace v3

} // namespace ranges

#endif // include guard
