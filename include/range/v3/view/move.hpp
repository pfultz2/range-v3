// Range v3 library
//
//  Copyright Eric Niebler 2013-2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_VIEW_MOVE_HPP
#define RANGES_V3_VIEW_MOVE_HPP

#include <utility>
#include <type_traits>
#include <range/v3/range_fwd.hpp>
#include <range/v3/size.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/range_traits.hpp>
#include <range/v3/range_adaptor.hpp>
#include <range/v3/range_concepts.hpp>
#include <range/v3/utility/pipeable.hpp>

namespace ranges
{
    inline namespace v3
    {
        namespace detail
        {
            template<typename T> T && rref(T &, int);
            template<typename T> T rref(T, long);
        }

        template<typename Rng>
        struct move_view
          : range_adaptor<move_view<Rng>, Rng>
        {
        private:
            friend range_access;
            struct adaptor : adaptor_base
            {
            private:
                using adaptor_base::prev;
            public:
                using single_pass = std::true_type;
                auto current(range_iterator_t<Rng> it) const ->
                    decltype(detail::rref(*it, 1))
                {
                    return std::move(*it);
                }
            };
            adaptor begin_adaptor() const
            {
                return {};
            }
            adaptor end_adaptor() const
            {
                return {};
            }
        public:
            move_view() = default;
            move_view(Rng &&rng)
              : range_adaptor_t<move_view>{std::forward<Rng>(rng)}
            {}
            CONCEPT_REQUIRES(SizedIterable<Rng>())
            range_size_t<Rng> size() const
            {
                return ranges::size(this->base());
            }
        };

        namespace view
        {
            struct move_fn : pipeable<move_fn>
            {
                template<typename Rng>
                move_view<Rng> operator()(Rng && rng) const
                {
                    CONCEPT_ASSERT(InputIterable<Rng>());
                    return move_view<Rng>{std::forward<Rng>(rng)};
                }
            };

            RANGES_CONSTEXPR move_fn move {};
        }
    }
}

#endif
