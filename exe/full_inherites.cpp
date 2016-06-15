#include <iostream>

template<
  typename T,
  typename... Args
> 
struct FullInherits : public T, FullInherits<Args...>
{
  using T::func;
};

template<typename T> 
struct FullInherits<T> : public T
{
  using T::func;
};

struct D
{
  static void func(float a) 
  {
    std::cout << "float 3" << std::endl;
  }
};

struct A 
{
  static void func(int a) 
  {
    std::cout << "int" << std::endl;
  }

  static void func2(int a)
  {
    std::cout << "func2 int" << std::endl;
  }
};

struct B
{
  static void func(float a) 
  {
    std::cout << "float" << std::endl;
  }
};

struct C
{
  static void func(float a) 
  {
    std::cout << "float 2" << std::endl;
  }
};


int main(void)
{
  FullInherits<A, B>::func((int)1);
  FullInherits<B, A>::func(1.0f);
  FullInherits<C, B, A>::func(1.0f);
  FullInherits<C, B, A, D>::func(1.0f);
  FullInherits<D, C, B, A, D>::func(1.0f);
}
