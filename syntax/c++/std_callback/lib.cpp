#include "lib.h"

int Lib::run(Fun fun, int a, int b)
{
    int result = 0;
    result = fun(a, b);
    return result;
}
