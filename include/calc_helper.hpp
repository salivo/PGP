#ifndef CALC_HELPER_HPP
#define CALC_HELPER_HPP
#include <string>
struct UnitPrefix {
    const char* prefix;
    int count;
    int exponent;
};

extern const UnitPrefix prefixes[];
UnitPrefix getUnitPrefixbByCount(int count);
UnitPrefix getUnitPrefixByNumber(float number);
int getPrefixCount();
std::string formatWithPrefix(float value, const std::string& unit);

#endif
