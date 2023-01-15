#include "toys/Any.h"
#include <iostream>

class A{
   public:
    A()=default;
    void Say(){
        std::cout << "Hello A" << std::endl;
    }
};

int main(){
    Any val1{1};
    std::cout << val1.Value<int>() << std::endl;
    Any val2{A()};
    val2.Value<A>().Say();
    val1 = val2;
    val1.Value<A>().Say();
    return 0;
}