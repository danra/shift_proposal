#include "shift_proposal.h"

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v1 {1, 2, 3, 4, 5};
    std::vector<int> v2 {1, 2, 3, 4, 5};
    
    shift(v1.begin(), v1.end(), 2);
    std::cout << "v1 after shift right by 2 = "; // 1 2 1 2 3
    for (auto& elem : v1)
        std::cout << elem << " ";
    std::cout << std::endl;

    shift(v2.begin(), v2.end(), -3);
    std::cout << "v2 after shift left by 3 = "; // 4 5 3 4 5
    for (auto& elem : v2)
        std::cout << elem << " ";
    std::cout << std::endl;
    
    return 0;
}
