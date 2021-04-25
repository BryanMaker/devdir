#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string ipstr = "192.168.0.1";
    const std::regex pattern("^([0-9]{1,3}\\.){0,3}[0-9]{0,3}$");
    if (std::regex_match(ipstr.c_str(), ipstr.c_str() + ipstr.length(), pattern))
    {
        std::cout << "匹配" << std::endl;
    }
    return 0;
}
