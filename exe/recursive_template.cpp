#include <iostream>

template <int N>
struct factrial
{
    static const int result = N * factrial<N - 1>::result;
};

template<>
struct factrial<0>
{
    static const int result = 1;
};

template <int N>
struct fib
{
    static const int result = fib<N - 1>::result + fib<N - 2>::result;
};

template<>
struct fib<0>
{
    static const int result = 1;
};

template<>
struct fib<1>
{
    static const int result = 1;
};


template <int N, int... remain>
struct sum
{
    static const int value = N + sum<remain...>::value;
};

template<int N>
struct sum<N>
{
    static const int value = N;
};

int main(void)
{
    int a = factrial<3>::result;
    int b = factrial<4>::result;
    int c = factrial<5>::result;
    int d = sum<1, 2, 3, 10>::value;
    int e = fib<50>::result;

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;

    return 0;
}
