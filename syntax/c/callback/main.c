#include "lib.h"
#include "stdio.h"

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 1;
    int b = 1;
    int result = 0;

    result = run(add, a, b);
    printf("result: %d\n", result);

    return 0;
}
