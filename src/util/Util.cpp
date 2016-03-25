#include "Util.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

std::string Util::readFile(std::string fileName) {
    ifstream file(fileName);

    if (file.fail()) {
        Util::log(Severity::ERROR, "Could not open file " + fileName);
    }

    string fileStr((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return fileStr;
}

void Util::log(Severity severity, string info) {
    time_t now = time(0);
    struct tm *timeinfo = localtime(&now);

    printf("[%d-%d-%d %d:%02d] ",
           timeinfo->tm_year + 1900,
           timeinfo->tm_mon + 1,
           timeinfo->tm_mday,
           timeinfo->tm_hour,
           timeinfo->tm_min);

    if (severity == Severity::ERROR) {
        printf(COLOR_RED "ERROR: " COLOR_RESET);
    } else if (severity == Severity::WARNING) {
        printf("WARNING: ");
    }

    printf("%s\n", info.c_str());
}
