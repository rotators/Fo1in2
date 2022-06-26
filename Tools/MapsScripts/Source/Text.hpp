#pragma once

#include <string>
#include <vector>

std::string TextGetReplaced(const std::string& text, const std::string& from, const std::string& to);
std::string TextGetUpper(const std::string& text);
bool TextReadFile(const std::string& filename, std::vector<std::string>& lines);
