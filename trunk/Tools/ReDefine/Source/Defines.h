#ifndef __DEFINES__
#define __DEFINES__

#include <map>
#include <string>
#include <vector>

namespace ReDefine
{
    struct Define
    {
        std::map<int, std::string> Values;
    };

    static std::map<std::string, Define>                   Defines;
    static std::map<std::string, std::vector<std::string>> VirtualDefines;

    bool ReadDefines( const std::string& path, const std::string& filename, const std::string& type, const std::string& prefix, const std::string& group = std::string() );

    void FinishDefines();
};

#endif // __DEFINES__ //
