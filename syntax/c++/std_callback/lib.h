#include <functional>

typedef std::function<int (int, int)> Fun;
class Lib
{
public:
    int run(Fun fun, int a, int b);
};
