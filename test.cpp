#include "shift_proposal.h"

#include <cassert>
#include <forward_list>
#include <vector>

int main()
{
    {
        std::vector<int> v {1, 2, 3, 4, 5};
        auto [first, last] = shift(v.begin(), v.end(), 2);
        assert((v == std::vector<int>{1, 2, 1, 2, 3}));
        assert((std::vector<int>{first, last} == std::vector<int>{1, 2, 3}));
    }

    {
        std::vector<int> v {1, 2, 3, 4, 5};
        auto [first, last] = shift(v.begin(), v.end(), -3);
        assert((v == std::vector<int>{4, 5, 3, 4, 5}));
        assert((std::vector<int>{first, last} == std::vector<int>{4, 5}));
    }
    
    {
        std::forward_list<int> flist {1, 2, 3, 4, 5};
        auto last = shift_left(flist.begin(), flist.end(), 3);
        assert((flist == std::forward_list<int>{4, 5, 3, 4, 5}));
        assert((std::forward_list<int>{flist.begin(), last} == std::forward_list<int>{4, 5}));
    }
    
    {
        std::vector<int> v {1, 2, 3, 4, 5};
        auto first = shift_right(v.begin(), v.end(), 2);
        assert((v == std::vector<int>{1, 2, 1, 2, 3}));
        assert((std::vector<int>{first, v.end()} == std::vector<int>{1, 2, 3}));
    }
    
    return 0;
}
