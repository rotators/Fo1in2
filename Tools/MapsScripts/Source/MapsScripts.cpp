/*
 * Copyright (c) 2015 Falltergeist developers
 * Copyright (c) 2022 Rotators
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

// C++ standard includes
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <string>

// map2json includes
#include "subtypes.h"

// Third party includes
#include "CommandLine.hpp"
#include "Text.hpp"

struct MapsScripts
{
    bool Verbose = false;

    std::string MapsDir;
    std::string ItemsDir;

    std::map<uint32_t, std::string> Script;
    std::set<uint32_t> ScriptUnused;

    std::map<uint32_t, uint32_t> Proto;

    std::map<std::string, std::set<uint32_t>> ByMap;
    std::map<uint32_t, std::set<std::string>> ByScript;
};

int Usage(int returnCode = EXIT_FAILURE)
{
    std::cout << "Usage: MapsScripts [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::cout << std::endl;
    std::cout << "  --maps [path]     Path to directory with .map files (required)" << std::endl;
    std::cout << "  --scripts [path]  Path to SCRIPTS.LST, can be file or directory (required)" << std::endl;
    std::cout << "  --items [path]    Path to directory with .map files" << std::endl;
    std::cout << "  --verbose         Enables extra debug messages" << std::endl;
    std::cout << std::endl;

    return returnCode;
}

uint32_t readUINT32(std::ifstream& stream)
{
    uint32_t value;
    char * buff = reinterpret_cast<char *>(&value);
    stream.read(buff, 4);
    std::reverse(buff, buff + 4);
    return value;
}

int32_t readINT32(std::ifstream& stream)
{
    return readUINT32(stream);
}

void skipUINT32(std::ifstream& stream, size_t count = 1)
{
    stream.seekg(count * 4, std::ios::cur);
}

void ReadMapObject(std::ifstream& stream, MapsScripts& info)
{
    skipUINT32(stream, 11);
    uint32_t PID = readUINT32(stream);

    uint32_t type = PID >> 24;
    uint32_t id  = PID & 0x00FFFFFF;

    if (info.Verbose)
        std::cout << "Read object PID " << PID << " type " << type << "" << id << std::endl;

    skipUINT32(stream, 4);

    readUINT32(stream); // SID1
    readUINT32(stream); // SID2

    int32_t inventorySize = readINT32(stream);

    skipUINT32(stream, 3);

    switch (type)
    {
        case 0: // items
        {
            uint32_t subtype = itemSubtype.at(id);
            switch (subtype)
            {
                case 0: // armor
                case 1: // container
                case 2: // drug
                    break;
                case 3: // weapon
                    readUINT32(stream);
                    readUINT32(stream);
                    break;
                case 4: // ammo
                case 5: // misc
                case 6: // key
                    skipUINT32(stream);
                    break;
            }
            break;
        }
        case 1: // critters:
            skipUINT32(stream, 10);
            break;
        case 2: // scenery
        {
            uint32_t subtype = scenerySubtype.at(id);
            switch (subtype)
            {
                case 0: // door
                    skipUINT32(stream);
                    break;
                case 1: // stairs
                case 2: // elevator
                case 3: // ladder bottom
                case 4: // ladder top
                    skipUINT32(stream, 2);
                    break;
                case 5: // generic
                    break;
            }
            break;
        }
        case 3:
            break;
        case 4:
            break;
        case 5:
        {
            switch(id)
            {
                case 12:
                    break;
                // Exit Grids
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                default:
                    skipUINT32(stream, 4);
                    break;
            }
            break;
        }
    }

    if (inventorySize > 0)
    {
        for (int32_t i = 0; i != inventorySize; ++i)
        {
            skipUINT32(stream);

            ReadMapObject(stream, info);
        }
    }
}

int ReadMap(const std::string& filename, MapsScripts& info)
{
    std::ifstream in;

    in.open(filename.c_str(), std::ios_base::binary | std::ios_base::in);
    if (!in.is_open())
    {
        std::cout << "Can't open file: " << filename << std::endl;
        return 1;
    }

    readUINT32(in); // version

    skipUINT32(in, 7);

    uint32_t localVars = readUINT32(in);

    // 4 - SID
    readUINT32(in);

    uint32_t flags = readUINT32(in);

    uint32_t elevations = 0;
    if ((flags & 2) == 0)
        elevations++;
    if ((flags & 4) == 0)
        elevations++;
    if ((flags & 8) == 0)
        elevations++;

    skipUINT32(in);

    uint32_t globalVars = readUINT32(in);

    skipUINT32(in, 46 + globalVars + localVars + (100 * 100 * elevations));

    // SCRIPTS SECTION
    for (unsigned int i = 0; i < 5; i++)
    {
        uint32_t count = readUINT32(in);
        if (count > 0)
        {
            short loop = count;
            if (count % 16 > 0)
                loop += 16 - count % 16;

            unsigned int check = 0;
            for (unsigned short j = 0; j < loop; j++)
            {
                {
                    uint32_t PID = readUINT32(in);

                    readUINT32(in); // unknown1

                    switch ((PID & 0xFF000000) >> 24)
                    {
                    case 1:
                        readUINT32(in); //unknown 2
                        readUINT32(in); //unknown 3
                        break;
                    case 2:
                        readUINT32(in); //unknown 2 next
                        break;
                    default:
                        break;
                    }
                    readUINT32(in); //unknown 4
                    uint32_t SID = readUINT32(in); // scriptId
                    readUINT32(in); //unknown 5
                    readUINT32(in); //unknown 6
                    readUINT32(in); //unknown 7
                    readUINT32(in); //unknown 8
                    readUINT32(in); //unknown 9
                    readUINT32(in); //unknown 10
                    readUINT32(in); //unknown 11
                    readUINT32(in); //unknown 12
                    readUINT32(in); //unknown 13
                    readUINT32(in); //unknown 14
                    readUINT32(in); //unknown 15
                    readUINT32(in); //unknown 16

                    if (j < count)
                    {
                        SID++;
                        info.ByScript[SID].insert(TextGetWithoutPath(info.MapsDir, filename));
                        info.ByMap[TextGetWithoutPath(info.MapsDir, filename)].insert(SID);
                        info.ScriptUnused.erase(SID);
                    }
                }

                if ((j % 16) == 15)
                {
                    uint32_t v = readUINT32(in);
                    check += v;

                    skipUINT32(in);
                }
            }
            if (check != count)
            {
                std::cout << "Check error!" << std::endl;
                return 1;
            }
        }
    }

    if (!info.ItemsDir.empty())
    {
        // OBJECTS section

        skipUINT32(in);

        for (unsigned int i = 0; i != elevations; ++i)
        {
            uint32_t objectsOnElevation = readUINT32(in);
            for (unsigned int j = 0; j != objectsOnElevation; ++j)
            {
                ReadMapObject(in, info);
            }
        }
    }

    in.close();

    return 0;
}

std::vector<std::string> GetMaps(const std::string& path, const std::string& extension)
{
    std::vector<std::string> result;

    for (const auto& file : std::filesystem::recursive_directory_iterator(path))
    {
        if (!std::filesystem::is_regular_file(file))
            continue;

        if (!extension.empty() && TextGetLower(file.path().extension().string()) != TextGetLower(extension))
            continue;

        result.push_back(file.path().string());
    }

    std::sort(result.begin(), result.end());

    return result;
}

int main(int argc, char** argv)
{
    MapsScripts info;
    std::cout << "MapsScripts <3 FO1@2" << std::endl << std::endl;

    // Handle command line arguments //

    CommandLine cmd(argc, argv);
    info.Verbose = cmd.IsOption("verbose");

    if (cmd.IsOption("help"))
        return Usage(EXIT_SUCCESS);

    if (cmd.IsOptionEmpty("maps") || cmd.IsOptionEmpty("scripts"))
        return Usage();

    std::string scriptsLst;
    std::vector<std::string> content;
    uint32_t scriptId = 0;

    info.MapsDir = cmd.GetStr("maps");
    scriptsLst = cmd.GetStr("scripts");
    if (cmd.IsOption("items"))
        info.ItemsDir = cmd.GetStr("items");
    else
        std::cout << "WARNING : items prototypes directory not set, skipping all objects" << std::endl << std::endl;

    if (!std::filesystem::is_directory(info.MapsDir))
    {
        std::cout << "ERROR : directory <" << info.MapsDir << "> does not exits" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::string> mapFiles = GetMaps(info.MapsDir, ".map");

    // Read scripts.lst //

    if (std::filesystem::is_directory(scriptsLst))
        scriptsLst = TextGetReplaced(scriptsLst + "/SCRIPTS.LST", "\\", "//");
    else if(std::filesystem::is_regular_file(scriptsLst))
        { }
    else
    {
        //
        return EXIT_FAILURE;
    }

    if (info.Verbose)
        std::cout << "Loading SCRIPTS.LST" << std::endl;

    if (!TextReadFile(scriptsLst, content))
        return 1;

    for (auto& line : content)
    {
        line = line.substr(0, line.find('#'));
        line = line.substr(0, line.find(';'));

        auto begin = line.find_first_not_of("\t ");
        auto end = line.find_last_not_of("\t ;#");

        info.Script[++scriptId] = line.substr(begin, end - begin + 1);
        info.ScriptUnused.insert(scriptId);
    }

    for (const auto& filename : mapFiles)
    {
        if (info.Verbose)
            std::cout << "Loading " << TextGetWithoutPath(info.MapsDir, filename) << std::endl;

        if (ReadMap(filename, info) != 0)
            return EXIT_FAILURE;
    }

    if (info.Verbose)
        std::cout << std::endl;

    for (const auto& it : info.ByMap)
    {
        std::cout << "Map " << it.first << std::endl;
        for (const auto& ti : it.second)
        {
            std::cout << "  " << std::setfill(' ') << std::setw(4) << ti << " " << info.Script[ti] << std::endl;
        }
    }

    std::cout << std::endl;

    for (const auto& it : info.ByScript)
    {
        std::cout << "Script " << it.first << " " << info.Script[it.first] << std::endl;
        for (const auto& ti : it.second)
        {
            std::cout << "  " << ti << std::endl;
        }
    }

    if (!info.ScriptUnused.empty())
    {
        std::cout << std::endl << "Unused" << std::endl;
        for (const auto& it : info.ScriptUnused)
        {
            std::cout << "  " << std::setfill(' ') << std::setw(4) << it << " " << info.Script[it] << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
