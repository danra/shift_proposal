#include "shift_proposal.h"

#include <array>
#include <cassert>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>

namespace {
    template<class Sequence>
    void test() {
        using std::begin;
        using std::end;

        constexpr int n = 5;

#ifdef __clang__
// Tell clang to shut up about std::array {} initializations.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-braces"
#endif // __clang__

        // shift left by i in [-2n, 3n)
        for (auto i = -2 * n; i < 3 * n; ++i) {
            auto const clamped = std::clamp(i, 0, n);
            Sequence s{1, 2, 3, 4, 5};
            auto control = {1, 2, 3, 4, 5};
            auto last = shift_left(begin(s), end(s), i);
            assert(std::equal(begin(control) + clamped, end(control), begin(s), last));
        }

        // shift left by i in [-2n, 3n) and fill
        for (auto i = -2 * n; i < 3 * n; ++i) {
            auto const clamped = std::clamp(i, 0, n);
            Sequence s{1, 2, 3, 4, 5};
            auto control = {1, 2, 3, 4, 5};
            auto last = shift_left(begin(s), end(s), i, 0);
            assert(std::equal(begin(control) + clamped, end(control), begin(s), last));
            assert(std::all_of(last, end(s), [](auto const& x){ return x == 0; }));
        }

        // shift right by i in [-2n, 3n)
        for (auto i = -2 * n; i < 3 * n; ++i) {
            auto const clamped = std::clamp(i, 0, n);
            Sequence s{1, 2, 3, 4, 5};
            auto control = {1, 2, 3, 4, 5};
            auto first = shift_right(begin(s), end(s), i);
            assert(std::equal(begin(control), end(control) - clamped, first, end(s)));
        }

        // shift right by i in [-2n, 3n) and fill
        for (auto i = -2 * n; i < 3 * n; ++i) {
            auto const clamped = std::clamp(i, 0, n);
            Sequence s{1, 2, 3, 4, 5};
            auto control = {1, 2, 3, 4, 5};
            auto first = shift_right(begin(s), end(s), i, 0);
            assert(std::equal(begin(control), end(control) - clamped, first, end(s)));
            assert(std::all_of(begin(s), first, [](auto const& x){ return x == 0; }));
        }
#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
    }
} // unnamed namespace

int main()
{
    test<std::array<int, 5>>();
    test<std::deque<int>>();
    test<std::forward_list<int>>();
    test<std::list<int>>();
    test<std::vector<int>>();
}
