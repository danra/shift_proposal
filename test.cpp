#include "shift_proposal.h"

#include <array>
#include <cassert>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>

namespace {

#ifdef __clang__
// Tell clang to shut up about std::array {} initializations.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-braces"
#endif // __clang__

    namespace detail {
        template<typename C, std::size_t... Is>
        constexpr auto generate_container_with_index_sequence(std::index_sequence<Is...>) -> C {
            return {std::integral_constant<std::size_t, Is>{}...};
        }
    } // namespace detail
    
    template<typename C, std::size_t N>
        constexpr auto generate_indexes() {
        return detail::generate_container_with_index_sequence<C>(std::make_index_sequence<N>{});
    }
    
    template<class Sequence, int n>
    void test() {
        using std::begin;
        using std::end;

        const auto control = generate_indexes<std::array<int, n>, n>();
        if constexpr (n == 5) {
            assert((control == std::array<int, 5> {0, 1, 2, 3, 4}));
        }
        
        // shift left by i in [-2n-2, 3n+3)
        for (auto i = -2 * n - 2; i < 3 * n + 3; ++i) {
            auto const clamped = std::clamp(i, 0, n);
            auto s = generate_indexes<Sequence, n>();
            auto const last = shift_left(begin(s), end(s), i);
            assert(std::equal(begin(control) + clamped, end(control), begin(s), last));
        }

        // shift left by i in [-2n-2, 3n+3) and fill
        for (auto i = -2 * n - 2; i < 3 * n + 3; ++i) {
            auto const clamped = std::clamp(i, 0, n);
            auto s = generate_indexes<Sequence, n>();
            auto const last = shift_left(begin(s), end(s), i, 0);
            assert(std::equal(begin(control) + clamped, end(control), begin(s), last));
            assert(std::all_of(last, end(s), [](auto const& x){ return x == 0; }));
        }
        
        // shift right by i in [-2n-2, 3n+3)
        for (auto i = -2 * n - 2; i < 3 * n + 3; ++i) {
            auto const clamped = std::clamp(i, 0, n);
            auto s = generate_indexes<Sequence, n>();
            auto const first = shift_right(begin(s), end(s), i);
            assert(std::equal(begin(control), end(control) - clamped, first, end(s)));
        }
        
        // shift right by i in [-2n-2, 3n+3) and fill
        for (auto i = -2 * n - 2; i < 3 * n + 3; ++i) {
            auto const clamped = std::clamp(i, 0, n);
            auto s = generate_indexes<Sequence, n>();
            auto const first = shift_right(begin(s), end(s), i, 0);
            assert(std::equal(begin(control), end(control) - clamped, first, end(s)));
            assert(std::all_of(begin(s), first, [](auto const& x){ return x == 0; }));
        }
    }
    
    template<int n>
    void testAll()
    {
        test<std::array<int, n>, n>();
        test<std::deque<int>, n>();
        test<std::forward_list<int>, n>();
        test<std::list<int>, n>();
        test<std::vector<int>, n>();
    }

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

} // unnamed namespace

int main()
{
    testAll<0>();
    testAll<1>();
    testAll<2>();
    testAll<3>();
    testAll<4>();
    testAll<5>();
    testAll<6>();
}
