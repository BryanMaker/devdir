#include "lib.h"

int Lib::run(int (User::*add)(int a, int b), User obj,  int a, int b)
{
    int result = 0;
    result = (obj.*add)(a, b);
    return result;
}
