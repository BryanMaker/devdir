#include <fstream>
#include <iostream>

int main(void)
{
    std::ifstream file("file.txt");
    /*
    std::string str;
    std::getline(file, str);
    std::cout << str << std::endl;
    */
    while (!file.eof())
    {
        
        float x, y, z;
        int r;
        file >> x;
        file >> y;
        file >> z;
        file >> r;

        if (file.fail())
        {
            break;
        }

        std::cout << x << " " << y << " " << z << " " << r << " " << std::endl;
    }


    return 0;
}
