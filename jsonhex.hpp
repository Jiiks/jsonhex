// https://github.com/Jiiks/jsonhex
#pragma once
#include <fstream>
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
            auto hexValue = match.str();
            auto value = strtoull(hexValue.c_str(), 0, 16);
            output.replace(output.find(hexValue), hexValue.length(), std::to_string(value));
            ++iter;
        }

        f.close();

        return nlohmann::json::parse(output);
    }
}
