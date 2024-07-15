#include "calc_helper.hpp"

std::string formatWithPrefix(float value, const std::string& unit) {
    // Define the prefixes and their corresponding multipliers
    const char* prefixes[] = {"", "k", "M", "G", "T", "P", "E"};
    int numPrefixes = sizeof(prefixes) / sizeof(prefixes[0]);

    // Determine the appropriate prefix
    int prefixIndex = 0;
    while (value >= 1000 && prefixIndex < numPrefixes - 1) {
        value /= 1000;
        ++prefixIndex;
    }

    // Buffer to store the formatted string
    char buffer[512];

    // Create the output string with the appropriate formatting
    if (value < 10.0) {
        sprintf(buffer, "%.1f %s%s", value, prefixes[prefixIndex], unit.c_str());
    } else {
        sprintf(buffer, "%.0f %s%s", value, prefixes[prefixIndex], unit.c_str());
    }

    return std::string(buffer);
}
