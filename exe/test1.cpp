#include <boost/optional.hpp>
#include <iostream>

void f(const boost::optional<int>& a)
{
    if (a){
        std::cout << "Just " << *a << std::endl;
    }
    else {
        std::cout << "Nothing" << std::endl;
    }
}

int main(void)
{
    boost::optional<int> a =  boost::optional<int>(10);
    boost::optional<int> b =  boost::optional<int>();

    f(a);
    f(b);
}
