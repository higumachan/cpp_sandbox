#include <vector>
#include <iostream>

template<class T>
struct remove_vectors {
    using type = T;
};

template<class T>
struct remove_vectors<std::vector<T>> {
    using type = typename remove_vectors<T>::type;
};

int main(int argc, char const* argv[])
{

    std::cout << typeid(std::vector<int>).name() << std::endl;
    std::cout << typeid(typename remove_vectors<std::vector<int>>::type).name() << std::endl;
    std::cout << typeid(typename remove_vectors<std::vector<std::vector<int>>>::type).name() << std::endl;

    return 0;
}
