// c语言可变参数函数，需要一个强制参数 + 数量可变可选参数
// 参数的数量从强制参数中取得，例如printf的格式化字符串
#include <stdarg.h>
#include <stdio.h>

double add(int n, ...);

int main(void)
{
    printf("%f \n", add(4, 1.0, 2.0, 3.0, 4.0));
    return 0;
}

double add(int n, ...)
{
    double sum = 0.0;
    va_list argPtr;// 声明参数列表
    va_start(argPtr, n);// 读取n个参数到列表中
    for (int i = 0; i < n; i++)
    {
        sum += va_arg(argPtr, double);// 从列表中取出一个参数，同时列表指向下一个参数
    }
    va_end(argPtr);

    return sum;
}
