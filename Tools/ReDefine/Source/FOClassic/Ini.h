/*
   MIT License

   Copyright (c) 2017-2018 Matthias C. M. Troffaes
   Copyright (c) 2018-2019 Rotators

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
 */

// This is modified version of IniPP library
// Original source https://github.com/mcmtroffaes/inipp/

#ifndef __INI__
#define __INI__

#include <istream>
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::string>              IniSection;
typedef std::map<std::string, IniSection>               IniSections;

typedef std::map<std::string, std::vector<std::string>> IniSectionsData;

class Ini
{
protected:
    IniSections     Sections;
    IniSectionsData SectionsRaw;
    IniSectionsData SectionsOrder;

public:
    // Any comments present are not removed when parsing file/string
    // Default: false
    bool KeepComments;

    // Content of all sections is saved as-is, including lines which does not follow "key=value" format
    // Default: false
    bool KeepSectionsRaw;

    // If order of all sections should be stored, value should be set to true before LoadFile() call
    // Otherwise, value should be set to true before calling SetStr()
    // Default: false
    bool KeepKeysOrder;

    Ini();
    virtual ~Ini();

    virtual bool LoadFile( const std::string& fname, bool unload = true );
    virtual bool LoadStr( const std::string& str, bool unload = true );
    virtual void Unload();

protected:
    virtual void Parse( std::basic_istream<char>& is );
    virtual void ParseString( const std::string& str );

public:
    virtual bool         IsSection( const std::string& section );
    virtual bool         IsSectionKey( const std::string& section, const std::string& key );
    virtual bool         IsSectionKeyEmpty( const std::string& section, const std::string& key );
    virtual unsigned int GetSections( std::vector<std::string>& sections );
    virtual unsigned int GetSectionKeys( const std::string& section, std::vector<std::string>& keys, bool ordered = false );

    virtual bool MergeSections( const std::string& to, const std::string& from, bool overwrite = false );
    virtual bool RemoveSection( const std::string& section );

public:
    // KeepSectionsRaw handling
    virtual bool                     IsSectionRaw( const std::string& section );
    virtual std::vector<std::string> GetSectionRaw( const std::string& section );
    virtual std::string              GetSectionRawString( const std::string& section, const std::string& separator );
protected:
    virtual void AddSectionRaw( const std::string& section, const std::string& line );
    virtual bool RemoveSectionRaw( const std::string& section );

protected:
    // KeepKeysOrder handling
    virtual bool IsSectionOrder( const std::string& section );
    virtual void AddSectionOrder( const std::string& section, const std::string& key );
    virtual bool RemoveSectionOrder( const std::string& section );

public:
    virtual bool                     GetBool( const std::string& section, const std::string& key, const bool& default_value );
    virtual int                      GetInt( const std::string& section, const std::string& key, const int& default_value, const unsigned char& base = 10 );
    virtual int                      GetHex( const std::string& section, const std::string& key, const int& default_value );
    virtual int                      GetOct( const std::string& section, const std::string& key, const int& default_value );
    virtual std::string              GetStr( const std::string& section, const std::string& key );
    virtual std::string              GetStr( const std::string& section, const std::string& key, const std::string& default_value );
    virtual std::vector<std::string> GetStrVec( const std::string& section, const std::string& key, char separator = ' ' );

    virtual void SetStr( const std::string& section, const std::string& key, std::string value );
};

#endif // __INI__ //
