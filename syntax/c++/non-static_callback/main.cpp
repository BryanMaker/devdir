#include <iostream>
#include "lib.h"

int main()
{
    Lib lib;
    User user;
    int a = 1;
    int b = 1;
    int result = 0;
    result = lib.run(&User::add, user, a, b);

    std::cout << "result: " << result << std::endl;
    return 0;
}
