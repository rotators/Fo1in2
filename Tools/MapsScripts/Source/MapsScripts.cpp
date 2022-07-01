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

uint32_t ReadUInt8(std::ifstream& stream)
{
    uint8_t value;
    char* buff = reinterpret_cast<char*>(&value);
    stream.read(buff, 1);
    return value;
}

uint32_t ReadUInt32(std::ifstream& stream)
{
    uint32_t value;
    char* buff = reinterpret_cast<char*>(&value);
    stream.read(buff, 4);
    std::reverse(buff, buff + 4);
    return value;
}

int32_t ReadInt32(std::ifstream& stream)
{
    return ReadUInt32(stream);
}

std::string ReadString(std::ifstream& stream, size_t size)
{
    size_t pos = stream.tellg();

    std::string result;
    std::getline(stream, result, '\0');
    stream.seekg(pos + size);

    return result;
}

void SkipUInt8(std::ifstream& stream, size_t count = 1)
{
    stream.seekg(count, std::ios::cur);
}

void SkipUInt16(std::ifstream& stream, size_t count = 1)
{
    SkipUInt8(stream, count * 2);
}


void SkipUInt32(std::ifstream& stream, size_t count = 1)
{
    SkipUInt8(stream, count * 4);
}

class MapsScripts
{
private:
    std::map<uint32_t, std::string> Script;

    std::map<uint32_t, uint32_t> ProtoItem;
    std::map<uint32_t, uint32_t> ProtoScenery;

public:
    bool Verbose;

    std::string MapsDir;
    std::string ProtoDir;

    std::map<std::string, std::set<std::string>> ByMap, ByScript;
    std::set<std::string> ScriptUnused;

    void AddSID(uint32_t sid, std::string script)
    {
        Script[sid] = script;
        ScriptUnused.insert(Script[sid]);
    }

    void UseSID(const int32_t& sid, const std::string& mapName, const std::string& suffix = "")
    {
        if (Script.count(sid))
        {
            ByScript[Script[sid] + suffix].insert(mapName);
            ByMap[mapName].insert(Script[sid] + suffix);

            if (ScriptUnused.contains(Script[sid]))
            {
                if (Verbose)
                    std::cout << "  ~ " << Script[sid] << std::endl;
                ScriptUnused.erase(Script[sid]);
            }
        }
        else
        {
            std::string name = "?!? UNKNOWN SCRIPT !?! (" + std::to_string(sid) + ")";
            ByScript[name].insert(mapName);
            ByMap[mapName].insert(name);
        }

    }

    uint32_t GetSubtype(uint32_t pid, std::map<uint32_t,uint32_t>& proto, const std::string& dir)
    {
        if (!proto.count(pid))
        {
            std::string filename = std::to_string(pid);
            filename = ProtoDir + "/" + dir + "/" + std::string(8 - filename.length(), '0') + filename;

            if (std::filesystem::is_regular_file(filename + ".PRO"))
                filename += ".PRO";
            else if (std::filesystem::is_regular_file(filename + ".pro"))
                filename += ".pro";
            else
            {
                if (dir == "items" && itemSubtype.count(pid))
                    return itemSubtype.at(pid);
                else if (dir == "scenery"&&scenerySubtype.count(pid))
                    return scenerySubtype.at(pid);

                return uint32_t(-1);
            }

            if (Verbose)
                std::cout << "  Loading " << filename << std::endl;

            std::ifstream stream;
            stream.open(filename.c_str(), std::ios_base::binary | std::ios_base::in);
            if (!stream.is_open())
            {
                std::cout << "Can't open file: " << filename << std::endl;
                return uint32_t(-1);
            }

            SkipUInt8(stream, 0x20);
            proto[pid] = ReadUInt32(stream);

        }

        return proto[pid];
    }

    uint32_t GetItemSubtype(uint32_t pid)
    {
        return GetSubtype(pid, ProtoItem, "items");
    }

    uint32_t GetScenerySubtype(uint32_t pid)
    {
        return GetSubtype(pid, ProtoScenery, "scenery");
    }
};

int Usage(int returnCode = EXIT_FAILURE)
{
    std::cout << "Usage: MapsScripts [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::cout << std::endl;
    std::cout << "  --maps [path]     Path to directory with .map files (required)" << std::endl;
    std::cout << "  --scripts [path]  Path to SCRIPTS.LST, can be file or directory (required)" << std::endl;
    std::cout << "  --proto [path]    Path to directory with .pro files" << std::endl;
    std::cout << "  --verbose         Enables extra debug messages" << std::endl;
    std::cout << std::endl;

    return returnCode;
}

int ReadMapObject(std::ifstream& stream, MapsScripts& info, const std::string& mapName)
{
    SkipUInt32(stream, 1);
    uint32_t pos = ReadInt32(stream);
    pos = pos;
    SkipUInt32(stream, 9);
    uint32_t PID = ReadUInt32(stream);

    uint32_t type = PID >> 24;
    uint32_t id  = PID & 0x00FFFFFF;

    //if (info.Verbose)
    //    std::cout << "Read object PID " << PID << " type " << type << "" << id << std::endl;

    SkipUInt32(stream, 5);  

    int32_t SID = ReadInt32(stream); // SID
    if (SID >= 0)
        info.UseSID(SID + 1, mapName, " (object data)");

    uint32_t inventorySize = ReadUInt32(stream);

    SkipUInt32(stream, 3);

    switch (type)
    {
        case 0: // items
        {
            //uint32_t subtype = itemSubtype.at(id);
            uint32_t subtype = info.GetItemSubtype(id);
            if (subtype == uint32_t(-1))
                return -1;
            switch (subtype)
            {
                case 0: // armor
                case 1: // container
                case 2: // drug
                    break;
                case 3: // weapon
                    SkipUInt32(stream, 2);
                    break;
                case 4: // ammo
                case 5: // misc
                case 6: // key
                    SkipUInt32(stream);
                    break;
            }
            break;
        }
        case 1: // critters:
            SkipUInt32(stream, 10);
            break;
        case 2: // scenery
        {
            //uint32_t subtype = scenerySubtype.at(id);
            uint32_t subtype = info.GetScenerySubtype(id);
            if (subtype == uint32_t(-1))
                return -1;

            switch (subtype)
            {
                case 0: // door
                    SkipUInt32(stream);
                    break;
                case 1: // stairs
                case 2: // elevator
                case 3: // ladder bottom
                case 4: // ladder top
                    SkipUInt32(stream, 2);
                    break;
                case 5: // generic
                    break;
            }
            break;
        }
        case 3:
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
                    SkipUInt32(stream, 4);
                    break;
            }
            break;
        }
    }

    if (inventorySize > 0)
    {
        for (uint32_t i = 0; i != inventorySize; ++i)
        {
            SkipUInt32(stream);

            if (ReadMapObject(stream, info, mapName) < 0)
                return -1;
        }
    }

    return 0;
}

int ReadMap(const std::string& filename, MapsScripts& info)
{
    std::ifstream in;

    in.open(filename.c_str(), std::ios_base::binary | std::ios_base::in);
    if (!in.is_open())
    {
        std::cout << "Can't open file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    ReadUInt32(in); // version

    std::string mapName = ReadString(in, 16);

    SkipUInt32(in, 3);

    uint32_t localVars = ReadUInt32(in);

    int32_t SID = ReadInt32(in);
    if(SID > 0)
        info.UseSID(SID, mapName);

    uint32_t flags = ReadUInt32(in);

    uint32_t elevations = 0;
    if ((flags & 2) == 0)
        elevations++;
    if ((flags & 4) == 0)
        elevations++;
    if ((flags & 8) == 0)
        elevations++;

    SkipUInt32(in);

    uint32_t globalVars = ReadUInt32(in);

    SkipUInt32(in, 46 + globalVars + localVars + (100 * 100 * elevations));

    // SCRIPTS SECTION
    for (unsigned int i = 0; i < 5; i++)
    {
        uint32_t count = ReadUInt32(in);
        if (count > 0)
        {
            short loop = count;
            if (count % 16 > 0)
                loop += 16 - count % 16;

            unsigned int check = 0;
            for (unsigned short j = 0; j < loop; j++)
            {
                {
                    uint32_t PID = ReadUInt32(in);

                    SkipUInt32(in);

                    switch ((PID & 0xFF000000) >> 24)
                    {
                    case 1:
                        SkipUInt32(in, 2);
                        break;
                    case 2:
                        SkipUInt32(in);
                        break;
                    default:
                        break;
                    }
                    SkipUInt32(in); //unknown 4
                    SID = ReadUInt32(in); // scriptId

                    if (j < count)
                    {
                        SID++;
                        info.UseSID(SID, mapName);
                    }

                    SkipUInt32(in, 12); //unknown 5
                }

                if ((j % 16) == 15)
                {
                    uint32_t v = ReadUInt32(in);
                    check += v;

                    SkipUInt32(in);
                }
            }
            if (check != count)
            {
                std::cout << "Check error!" << std::endl;
                return 1;
            }
        }
    }

    if (!info.ProtoDir.empty())
    {
        // OBJECTS section

        SkipUInt32(in);

        for (unsigned int i = 0; i != elevations; ++i)
        {
            uint32_t objectsOnElevation = ReadUInt32(in);
            for (unsigned int j = 0; j != objectsOnElevation; ++j)
            {
                if (ReadMapObject(in, info, mapName) < 0)
                    break;
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

        if (!extension.empty() && TextGetUpper(file.path().extension().string()) != TextGetUpper(extension))
            continue;

        result.push_back(file.path().string());
    }

    std::sort(result.begin(), result.end());

    return result;
}

int main(int argc, char** argv)
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);

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

    info.MapsDir = cmd.GetStr("maps");
    scriptsLst = cmd.GetStr("scripts");
    if (cmd.IsOption("proto"))
        info.ProtoDir = cmd.GetStr("proto");
    else
        std::cout << "WARNING : prototypes directory not set, skipping all objects" << std::endl << std::endl;

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

    int32_t SID = 1;
    for (auto& line : content)
    {

        line = TextGetUpper(line);

        line = line.substr(0, line.find('#'));
        line = line.substr(0, line.find(';'));

        auto begin = line.find_first_not_of("\t ");
        auto end = line.find_last_not_of("\t ;#");

        info.AddSID(SID++, line.substr(begin, end - begin + 1));
    }

    for (const auto& filename : mapFiles)
    {
        if (info.Verbose)
            std::cout << "Loading " << filename << std::endl;

        if (ReadMap(filename, info) != 0)
            return EXIT_FAILURE;
    }

    if (info.Verbose)
        std::cout << std::endl;

    for (const auto& it : info.ByMap)
    {
        std::cout << it.first << std::endl;
        for (const auto& ti : it.second)
        {
            std::cout << "  " << ti << std::endl;
        }
    }

    std::cout << std::endl << std::string(16, '-') << std::endl << std::endl;

    for (const auto& it : info.ByScript)
    {
        std::cout << it.first << std::endl;
        for (const auto& ti : it.second)
        {
            std::cout << "  " << ti << std::endl;
        }
    }

    if (!info.ScriptUnused.empty())
    {
        std::cout << std::endl << "Possibly unused" << std::endl;
        for (const auto& it : info.ScriptUnused)
        {
            std::cout << "  " << it << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
