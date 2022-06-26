#pragma once

#include <string>
#include <vector>

std::string TextGetReplaced(const std::string& text, const std::string& from, const std::string& to);
std::string TextGetLower(const std::string& text);
std::string TextGetWithoutPath(const std::string& path, const std::string& filename);
bool TextReadFile(const std::string& filename, std::vector<std::string>& lines);
