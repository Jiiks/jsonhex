#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
// include correctly in your project
#include <nlohmann/json.hpp>

namespace jsonhex {
    const std::regex jsonhexPattern("0x([0-9A-Fa-f]+)");
    static nlohmann::json parse(const char* fPath) {
        std::ifstream f(fPath);
        std::string content((std::istreambuf_iterator<char>(f)),
            std::istreambuf_iterator<char>());
        

        std::sregex_iterator iter(content.begin(), content.end(), jsonhexPattern);
        std::sregex_iterator end;
        std::string output = content;

        while(iter != end) {
            std::smatch match = *iter;
            std::string hexValue = match[1].str();

            std::istringstream converter(hexValue);
            uint64_t intValue;
            converter >> std::hex >> intValue;

            output.replace(output.find("0x" + hexValue), ("0x" + hexValue).size(), std::to_string(intValue));
            ++iter;
        }

        f.close();

        return nlohmann::json::parse(output);
    }
}
