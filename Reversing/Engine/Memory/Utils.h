#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace sfall 
{

// splits a string by given delimiter
// taken from: http://stackoverflow.com/a/236803/4331475
template<typename T>
void split(const std::string &s, char delim, T result, size_t limit = -1) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	size_t i = 0;
	while (std::getline(ss, item, delim) && (limit == -1 || i < limit)) {
		*(result++) = item;
		i++;
	}
}

// Splits a string by given delimiter
std::vector<std::string> split(const std::string &s, char delim);

std::string trim(const std::string& str);

void ToLowerCase(std::string& line);

bool isSpace(char c);

void strtrim(char* str);

}
