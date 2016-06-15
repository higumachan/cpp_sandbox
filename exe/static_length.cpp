#include <iostream>

#define SSTRLEN(s) (sizeof(s))
#define BLANKS(0) ""
#define BLANKS(n) " "BLANKS((n) - 1)

#define S1 "test1"
#define S2 "test12"

int main(void)
{
    std::cout << BLANKS(10) << std::endl;
}
