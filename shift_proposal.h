#pragma once

#include <algorithm>

template<class BidirIt> // TODO: shifting elements left should also be allowed for forward iterators
void shift(BidirIt first, BidirIt last, int n)
{
    if (n == 0)
        return;

    // Shift elements right (forward)
    if (n > 0)
        std::move_backward(first, last - n, last);
    
    // Shift elements left (backward)
    else
        std::move(first - n, last, first);
}
