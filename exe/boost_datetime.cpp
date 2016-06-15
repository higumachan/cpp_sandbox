#include <iostream>
#include "boost/date_time.hpp"

int main(void)
{
    auto p1 = boost::posix_time::from_iso_string("20150601T000000.000000");
    boost::posix_time::ptime p2;
    try {
        p2 = boost::posix_time::from_iso_string("20150231T000000.000000");
    }
    catch (boost::gregorian::bad_day_of_month& ex){
        std::cout << "era---" << std::endl;
    }
    auto p3 = boost::posix_time::from_iso_string("2016K0231T000000.0000");

    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    //std::cout << p3 << std::endl;
}

