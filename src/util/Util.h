#ifndef BILLIARDS_UTIL_H
#define BILLIARDS_UTIL_H

#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>

using namespace std;

enum Severity {
    ERROR, WARNING, INFO
};

class Util {
public:
    static constexpr double EPSILON = 0.00001;

    static string readFile(string file);

    static void log(Severity type, string error);
};

#endif //BILLIARDS_UTIL_H
