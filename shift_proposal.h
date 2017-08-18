#ifndef SHIFT_PROPOSAL_H
#define SHIFT_PROPOSAL_H

#include <algorithm>
#include <cassert>
#include <iterator>
#include <optional>
#include <utility>

template<class BidirIt>
std::pair<BidirIt, BidirIt> shift(BidirIt first, BidirIt last, typename std::iterator_traits<BidirIt>::difference_type n, std::optional<typename std::iterator_traits<BidirIt>::value_type> filler = std::nullopt)
{
    if (n == 0)
        return { first, last };

    // Shift elements right (forward)
    if (n > 0)
    {
        auto shifted_first = std::move_backward(first, std::prev(last, n), last);
        if (filler.has_value())
            std::fill(first, shifted_first, *filler);
        return { shifted_first, last };
    }
    
    // n < 0
    // Shift elements left (backward)
    auto shifted_last = std::move(std::next(first, -n), last, first);
    if (filler.has_value())
        std::fill(shifted_last, last, *filler);
    return { first, shifted_last };
}

template<class ForwardIt>
ForwardIt shift_left(ForwardIt first, ForwardIt last, typename std::iterator_traits<ForwardIt>::difference_type n, std::optional<typename std::iterator_traits<ForwardIt>::value_type> filler = std::nullopt)
{
    assert(n >= 0);
    if (n == 0)
        return last;
    auto shifted_last = std::move(std::next(first, n), last, first);
    if (filler.has_value())
        std::fill(shifted_last, last, *filler);
    return shifted_last;
}

template<class BidirIt>
BidirIt shift_right(BidirIt first, BidirIt last, typename std::iterator_traits<BidirIt>::difference_type n, std::optional<typename std::iterator_traits<BidirIt>::value_type> filler = std::nullopt)
{
    assert(n >= 0);
    if (n == 0)
        return first;
    auto shifted_first = std::move_backward(first, std::prev(last, n), last);
    if (filler.has_value())
        std::fill(first, shifted_first, *filler);
    return shifted_first;
}

#endif // !defined(SHIFT_PROPOSAL_H)
