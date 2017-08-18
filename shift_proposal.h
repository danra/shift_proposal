#ifndef SHIFT_PROPOSAL_H
#define SHIFT_PROPOSAL_H

#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>

template<class BidirIt>
std::pair<BidirIt, BidirIt> shift(BidirIt first, BidirIt last, typename std::iterator_traits<BidirIt>::difference_type n)
{
    if (n == 0)
        return { first, last };

    // Shift elements right (forward)
    if (n > 0)
        return { std::move_backward(first, std::prev(last, n), last), last };

    // n < 0
    // Shift elements left (backward)
    return { first, std::move(std::next(first, -n), last, first) };
}

template<class ForwardIt>
ForwardIt shift_left(ForwardIt first, ForwardIt last, typename std::iterator_traits<ForwardIt>::difference_type n)
{
    assert(n >= 0);
    if (n == 0)
        return last;
    return std::move(std::next(first, n), last, first);
}

#endif // !defined(SHIFT_PROPOSAL_H)
