#include "toys/vt_logger.h"




using namespace cxxcoll;
int main() {
    short s = 1;
    int i = 2;
    long l = 3;
    float f = 4;
    double d = 5;
    short& ls = s;
    int&& ri = 7;
    const long cl = 8;
    const float& cf = f;
    std::string str = "Hello";

    toy::Logger::Log("Show val: {}, {}, {}, {}, {}, {}, {}, {}, {}, {} {}", s, i, l, f, d, ls, ri,
                     cl, cf, str, "World");

}