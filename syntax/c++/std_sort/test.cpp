#include <vector>
#include <algorithm> // sort
#include <functional> // greater
#include <iostream>

int main(void)
{
    std::vector<double> diss = {5, 8, 2, 1, 0, 3, 4, 1};
    for (auto i : diss) {
        std::cout << i << std::endl;;
    }
    std::sort(diss.begin(), diss.end(), std::greater<double>());
    std::cout << "####################" << std::endl;
    for (auto i : diss) {
        std::cout << i << std::endl;
    }
    return 0;
}
