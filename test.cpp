#include "shift_proposal.h"

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v1 {1, 2, 3, 4, 5};
    std::vector<int> v2 {1, 2, 3, 4, 5};
    
    {
        auto [first, last] = shift(v1.begin(), v1.end(), 2);

        std::cout << "v1 after shift right by 2 = "; // 1 2 1 2 3
        for (auto& elem : v1)
            std::cout << elem << " ";
        std::cout << std::endl;

        std::cout << "v1 shifted elements = "; // 1 2 3
        for (auto it = first; it != last; ++it)
            std::cout << *it << " ";
        std::cout << std::endl;
    }

    {
        auto [first, last] = shift(v2.begin(), v2.end(), -3);

        std::cout << "v2 after shift left by 3 = "; // 4 5 3 4 5
        for (auto& elem : v2)
            std::cout << elem << " ";
        std::cout << std::endl;

        std::cout << "v2 shifted elements = "; // 4 5
        for (auto it = first; it != last; ++it)
            std::cout << *it << " ";
        std::cout << std::endl;
    }
    
    return 0;
}
