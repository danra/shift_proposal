#ifndef SHIFT_PROPOSAL_H
#define SHIFT_PROPOSAL_H

#include <algorithm>
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

#endif // !defined(SHIFT_PROPOSAL_H)
