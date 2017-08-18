#ifndef SHIFT_PROPOSAL_H
#define SHIFT_PROPOSAL_H

#include <algorithm>
#include <iterator>

template<class BidirIt> // TODO: shifting elements left should also be allowed for forward iterators
void shift(BidirIt first, BidirIt last, typename std::iterator_traits<BidirIt>::difference_type n)
{
    if (n == 0)
        return;

    // Shift elements right (forward)
    if (n > 0)
        std::move_backward(first, std::prev(last, n), last);
    
    // Shift elements left (backward)
    else
        std::move(std::next(first, -n), last, first);
}

#endif // !defined(SHIFT_PROPOSAL_H)
