// Range v3 library
//
//  Copyright Eric Niebler 2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_VIEW_GENERATE_N_HPP
#define RANGES_V3_VIEW_GENERATE_N_HPP

#include <utility>
#include <type_traits>
#include <range/v3/range_fwd.hpp>
#include <range/v3/size.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/range_traits.hpp>
#include <range/v3/range_facade.hpp>
#include <range/v3/utility/invokable.hpp>
#include <range/v3/utility/optional.hpp>

namespace ranges
{
    inline namespace v3
    {
        template<typename G>
        struct generate_n_view
          : range_facade<generate_n_view<G>>
        {
        private:
            friend struct range_access;
            optional<G> gen_;
            std::size_t n_;
            template<bool IsConst>
            struct cursor
            {
            private:
                using gen_t = detail::add_const_if_t<G, IsConst>;
                gen_t *gen_;
                std::size_t n_;
            public:
                using single_pass = std::true_type;
                cursor() = default;
                cursor(gen_t &g, std::size_t n)
                  : gen_(&g), n_(n)
                {}
                constexpr bool done() const
                {
                    return 0 == n_;
                }
                auto current() const -> decltype((*gen_)())
                {
                    return (*gen_)();
                }
                void next()
                {
                    RANGES_ASSERT(0 != n_);
                    --n_;
                }
            };
            CONCEPT_REQUIRES(!Function<G const>())
            cursor<false> begin_cursor()
            {
                RANGES_ASSERT(!!gen_);
                return {*gen_, n_};
            }
            CONCEPT_REQUIRES(Function<G const>())
            cursor<true> begin_cursor() const
            {
                RANGES_ASSERT(!!gen_);
                return {*gen_, n_};
            }
        public:
            generate_n_view() = default;
            explicit generate_n_view(G g, std::size_t n)
              : gen_(std::move(g)), n_(n)
            {}
        };

        namespace view
        {
            struct generate_n_fn
            {
                template<typename G, CONCEPT_REQUIRES_(Function<G>())>
                generate_n_view<G> operator()(G g, std::size_t n) const
                {
                    return generate_n_view<G>{std::move(g), n};
                }
            };

            RANGES_CONSTEXPR generate_n_fn generate_n{};
        }
    }
}

#endif
