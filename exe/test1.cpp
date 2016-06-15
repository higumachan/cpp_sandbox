#include <boost/optional.hpp>
#include <iostream>

template<typename Type>
struct Wrapper : Type
{

};

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

    Wrapper<float> c;
    
}
