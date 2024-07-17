#include "calc_helper.hpp"
#include <cstring>
#include <string>

const UnitPrefix prefixes[] = {
    {"", 0, 0},
    {"k", 1, 3},
    {"M", 2, 6},
    {"G", 3, 9},
    {"T", 4, 12},
    {"P", 5, 15},
    {"E", 6, 18}
};

int getPrefixCount() {
    return sizeof(prefixes) / sizeof(prefixes[0]);
}

UnitPrefix getUnitPrefixbByString(char* prefix){
    for (int i = 0; i<getPrefixCount(); i++){
        if(strcmp(prefix, prefixes[i].prefix) == 0) return prefixes[i];
    }
    return prefixes[0];
}

UnitPrefix getUnitPrefixByNumber(float number){
    int prefixIndex = 0;
    while (number >= 1000 && prefixIndex < getPrefixCount() - 1) {
        number /= 1000;
        ++prefixIndex;
    }
    return prefixes[prefixIndex];
}


std::string formatWithPrefix(float value, const std::string& unit) {
    // Determine the appropriate prefix
    int prefixIndex = 0;
    int numPrefixes = sizeof(prefixes) / sizeof(prefixes[0]);

    while (value >= 1000 && prefixIndex < numPrefixes - 1) {
        value /= 1000;
        ++prefixIndex;
    }

    // Buffer to store the formatted string
    char buffer[512];

    // Create the output string with the appropriate formatting
    if (value < 10.0) {
        snprintf(buffer, sizeof(buffer), "%.1f %s%s", value, prefixes[prefixIndex].prefix, unit.c_str());
    } else {
        snprintf(buffer, sizeof(buffer), "%.0f %s%s", value, prefixes[prefixIndex].prefix, unit.c_str());
    }

    return std::string(buffer);
}
