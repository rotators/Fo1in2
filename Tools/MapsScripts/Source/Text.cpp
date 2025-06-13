#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "Text.hpp"

std::string TextGetReplaced(const std::string& text, const std::string& from, const std::string& to)
{
    std::string                 result;

    std::string::const_iterator textCurrent = text.begin();
    std::string::const_iterator textEnd = text.end();
    std::string::const_iterator next = std::search(textCurrent, textEnd, from.begin(), from.end());

    while (next != textEnd)
    {
        result.append(textCurrent, next);
        result.append(to);
        textCurrent = next + from.size();
        next = std::search(textCurrent, textEnd, from.begin(), from.end());
    }

    result.append(textCurrent, next);

    return result;
}

std::string TextGetUpper(const std::string& text)
{
    std::string result = text;

    std::ranges::transform(result, result.begin(), [](unsigned char c) { return std::toupper(c); });

    return result;
}

bool TextReadFile(const std::string& filename, std::vector<std::string>& lines)
{
    lines.clear();

    const std::string file = TextGetReplaced(filename, "\\", "/");
    if (!std::filesystem::exists(file))
    {
        std::cout << "WARNING : cannot find file<" << file << ">" << std::endl;
        return false;
    }

    // don't waste time on empty files
    if (std::filesystem::is_empty(file))
        return true;

    std::ifstream fstream;
    fstream.open(file, std::ios_base::in | std::ios_base::binary);

    bool result = fstream.is_open();
    if (result)
    {
        // https://stackoverflow.com/a/22986486/11998612
        fstream.ignore(std::numeric_limits<std::streamsize>::max());
        std::streamsize size = fstream.gcount();
        fstream.clear();
        fstream.seekg(0, std::ifstream::beg);

        if (size >= 3)
        {
            // skip bom
            char bom[3] = { 0, 0, 0 };
            fstream.read(bom, sizeof(bom));
            if (bom[0] != static_cast<char>(0xEF) || bom[1] != static_cast<char>(0xBB) || bom[2] != static_cast<char>(0xBF))
                fstream.seekg(0, std::ifstream::beg);
            else
            {
                size -= 3;
                if (!size)
                    return true;
            }
        }

        std::string line;
        while (std::getline(fstream, line, '\n'))
        {
            lines.push_back(TextGetReplaced(line, "\r", ""));
        }
    }
    else
        std::cout << "WARNING : cannot read file<" << file << ">" << std::endl;

    return result;
}
