#include <iostream>

class A;
class B;
class C;

class A 
{
    friend C;
public:
    A() : var1(10) {}
private:
    int var1;
};

class B : public A
{
public:
    B() : var2(100) {}
private:
    int var2;
};

class C
{
public:
    int method1()
    {
        std::cout << b.var1 << std::endl;
    }
    int method2()
    {
        //std::cout << b.var2 << std::endl;
    }
private:
    B b;
};




int main(void)
{
    C c;

    c.method1();
    c.method2();
}
