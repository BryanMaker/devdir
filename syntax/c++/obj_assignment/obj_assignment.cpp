#include <iostream>

using namespace std;

class Temp
{
public:
    int id;
};

int main(void)
{
    Temp tmpa;
    tmpa.id = 1;
    Temp tmpb = tmpa;
    tmpa.id = 2;

    cout << "tmpa id: " << tmpa.id << endl
        << "tmpb id: " << tmpb.id << endl;

    cout << "\n" << endl;

    Temp tmpc;
    tmpc.id = 1;
    Temp& tmpd = tmpc;
    tmpc.id = 2;

    cout << "tmpc id: " << tmpc.id << endl
        << "tmpd id: " << tmpd.id << endl;

    return 0;
}
