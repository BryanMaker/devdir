#include <iostream>

int main()
{
    unsigned char* sendptr[3];
    unsigned char c1data[] = { 0xCD,0x00,0x02,0x00,0x0A }; // 设置旋转速度[2]
    unsigned char c2data[] = { 0xCE, 0x0F, 0x00, 0x00, 0x01, 0x0A }; // 设置旋转一整圈
    unsigned char c3data[] = { 0xC1,0x0A }; // 启用电机
    sendptr[0] = c1data;
    sendptr[1] = c2data;
    sendptr[2] = c3data;

    for (int i = 0; i < sizeof(sendptr) / sizeof(sendptr[0]); i++)
    {
        std::cout << i << ": " << sendptr[i] << std::endl;
    }

    return 0;
}
