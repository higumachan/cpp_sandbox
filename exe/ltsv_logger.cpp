#include "easylogging++.h"
#include "ltsv_keyvalues.hpp"

#define _ELPP_THREAD_SAFE 1
#define _ELPP_STACKTRACE_ON_CRASH 1

_INITIALIZE_EASYLOGGINGPP

int main(void)
{
    LOG(INFO) <<  get_ltsv_keyvalues(
        std::string("test"), std::string("nadeko"),
        std::string("test2"), std::string("nadeko2")
    );
}
