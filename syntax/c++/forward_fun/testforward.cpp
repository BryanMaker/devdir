#include <utility> // std::forward
#include <iostream>

void overloaded(const int& x)
{
    std::cout << "[lvalue]" << std::endl;
}

void overloaded(int&& x)
{
    std::cout << "[rvalue]" << std::endl;
}

//使用右值引用推导类型的函数模板：
template<typename T>
void fun(T&& x)
{
    overloaded(x); // 总是左直
    overloaded(std::forward<T>(x)); // 如果参数是右值，则右值
}

int main()
{
    return 0;
}
