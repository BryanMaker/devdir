#include <fstream>
#include <iostream>

int main(void)
{
    std::ifstream file("file.txt");
    std::string str;
    std::getline(file,str);
    std::cout << str << std::endl;

    return 0;
}
