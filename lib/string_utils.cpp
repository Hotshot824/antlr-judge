#include <iostream>
#include <string>

class StringUtils {
public:
    static std::string replace(const std::string& str, const std::string& find, const std::string& replace) {
        std::string result = str;
        size_t pos = 0;
        while ((pos = result.find(find, pos)) != std::string::npos) {
            result.replace(pos, find.length(), replace);
            pos += replace.length();
        }
        return result;
    }
};