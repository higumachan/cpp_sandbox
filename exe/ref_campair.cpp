#include <iostream>
#include <memory>

int main(void)
{
    int a = 1;
    int b = 1;

    int& c = a;
    int& d = b;
    std::weak_ptr<int> e;
    std::weak_ptr<int> f;

    e = &a;
    f = &b;
    std::cout << "c == c:" << (c == c) << std::endl;
    std::cout << "c == d:" << (c == d) << std::endl;
    std::cout << "d == c:" << (d == c) << std::endl;

    return 0;
}
