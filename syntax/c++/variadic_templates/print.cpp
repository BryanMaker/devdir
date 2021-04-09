#include <iostream>

template <typename... T>
void fun(T... args)
{
    // sizeof和sizeof...是运算符，并不是函数
    std::cout << sizeof...(args) << std::endl;
}

int main(int argc, char const* argv[])
{
    if (argc > 1)
    {
        std::cout << argv[0] << std::endl;
    }

    fun(0, 0.0, "hello");
    return 0;
}
