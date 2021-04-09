#include <iostream>
#include "lib.h"
#include "user.h"

int main()
{
    Lib lib;
    User user;
    int a = 1;
    int b = 1;
    int result = 0;

    Fun fun = std::bind(&User::add, user, std::placeholders::_1, std::placeholders::_2);
    result = lib.run(fun, a, b);

    std::cout << "result: " << result << std::endl;
    return 0;
}
