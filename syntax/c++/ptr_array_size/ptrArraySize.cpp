#include <iostream>

int main()
{
    unsigned char* sendptr[3];
    unsigned char c1data[] = { 0xcd, 0x00, 0x02, 0x00, 0x0a };
    unsigned char c2data[] = { 0xce, 0x0f, 0x00, 0x01, 0x0a };
    unsigned char c3data[] = { 0xc1, 0x0a };
    sendptr[0] = c1data;
    sendptr[1] = c2data;
    sendptr[2] = c3data;

    for (int i = 0; i < sizeof(sendptr) / sizeof(sendptr[0]); i++)
    {
        std::cout << i << ": " << sendptr[i] << std::endl;
    }

    return 0;
}
