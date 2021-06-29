#include <fstream>
#include <iostream>

int main(void)
{
    std::ifstream file("dataHasRssi.txt");
    std::filebuf* pbuf = file.rdbuf();

    std::size_t size = pbuf->pubseekoff(0, file.end, file.in);
    pbuf->pubseekpos(0, file.in);

    size = 100;
    char* buffer = new char[size];

    pbuf->sgetn(buffer, size);

    std::string str(buffer, size);

    std::cout << str << std::endl;
    
    return 0;
}
