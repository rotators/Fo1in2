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

#ifdef FOCLASSIC_ENGINE
# include "Core.h"
#endif

#include <errno.h>

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <fstream>
#include <functional>
#include <istream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Ini.h"

using namespace std;

#define SECTION_START    '['
#define SECTION_END      ']'
#define KEY_ASSIGN       '='

static vector<char> CommentChars;

inline void TrimLeft( string& str )
{
    str.erase( str.begin(), find_if( str.begin(), str.end(), not1( ptr_fun<int, int>( isspace ) ) ) );
}

inline void TrimRight( string& str )
{
    str.erase( find_if( str.rbegin(), str.rend(), not1( ptr_fun<int, int>( isspace ) ) ).base(), str.end() );
}

inline void Cleanup( string& str )
{
    str.erase( remove( str.begin(), str.end(), '\r' ), str.end() );
    str.erase( remove( str.begin(), str.end(), '\n' ), str.end() );
    replace( str.begin(), str.end(), '\t', ' ' );
}

//

Ini::Ini() : KeepComments( false ), KeepSectionsRaw( false ), KeepKeysOrder( false )
{
    #if defined (FOCLASSIC_ENGINE) && defined (FO_WINDOWS) && defined (FO_MSVC) && _MSC_VER >= 1910 && !defined (__INTELLISENSE__)
    # pragma TODO("Use initializer list for CommentChars")
    #endif
    if( CommentChars.empty() )
    {
        CommentChars.push_back( '#' );
        CommentChars.push_back( ';' );
    }
}

Ini::~Ini()
{
    Unload();
}

//

bool Ini::LoadFile( const string& fname, bool unload /* = true */ )
{
    if( unload )
        Unload();

    ifstream fstream;
    fstream.open( fname, ios_base::in | ios_base::binary );

    if( fstream.is_open() )
    {
        char bom[3] = { 0, 0, 0 };
        fstream.read( bom, sizeof(bom) );
        if( bom[0] != (char)0xEF || bom[1] != (char)0xBB || bom[2] != (char)0xBF )
            fstream.seekg( 0, fstream.beg );

        Parse( fstream );

        return true;
    }

    return false;
}

bool Ini::LoadStr( const string& str, bool unload /* = true */ )
{
    if( unload )
        Unload();
    ParseString( str );

    return true;
}

void Ini::Unload()
{
    Sections.clear();
    SectionsRaw.clear();
    SectionsOrder.clear();
}

//

void Ini::Parse( basic_istream<char>& stream )
{
    string line;
    string section;

    while( !stream.eof() )
    {
        getline( stream, line );

        Cleanup( line );

        if( !KeepComments )
        {
            for( auto it = CommentChars.begin(), end = CommentChars.end(); it != end; ++it )
            {
                line = line.substr( 0, line.find( *it ) );
            }
        }

        TrimLeft( line );
        TrimRight( line );

        const size_t length = line.length();

        if( !length || line.empty() )
            continue;

        const size_t pos = line.find_first_of( KEY_ASSIGN );
        const char&  front = line.front();

        if( front == SECTION_START )
        {
            if( line.back() == SECTION_END )
                section = line.substr( 1, length - 2 );
        }
        else if( pos != 0 && pos != string::npos )
        {
            string key( line.substr( 0, pos ) );
            string value( line.substr( pos + 1, length ) );

            TrimRight( key );
            TrimLeft( value );

            if( !IsSectionKey( section, key ) )
                SetStr( section, key, value );

            if( KeepSectionsRaw )
                AddSectionRaw( section, line );
        }
        else if( KeepSectionsRaw )
            AddSectionRaw( section, line );
    }
}

void Ini::ParseString( const string& str )
{
    stringstream buf;
    buf << str;

    Parse( buf );
}

//

bool Ini::IsSection( const string& section )
{
    return Sections.find( section ) != Sections.end();
}

bool Ini::IsSectionKey( const string& section, const string& key )
{
    if( !IsSection( section ) )
        return false;

    return Sections[section].find( key ) != Sections[section].end();
}

bool Ini::IsSectionKeyEmpty( const string& section, const string& key )
{
    if( !IsSectionKey( section, key ) )
        return true;

    return Sections[section][key].empty();
}

unsigned int Ini::GetSections( vector<string>& sections )
{
    unsigned int count = 0;

    for( IniSections::iterator it = Sections.begin(); it != Sections.end(); ++it, count++ )
    {
        sections.push_back( it->first );
    }

    return count;
}

unsigned int Ini::GetSectionKeys( const string& section, vector<string>& keys, bool ordered /* = false */ )
{
    unsigned int count = 0;

    if( IsSection( section ) )
    {
        if( ordered )
        {
            for( vector<string>::iterator it = SectionsOrder[section].begin(); it != SectionsOrder[section].end(); ++it )
            {
                keys.push_back( *it );
                count++;
            }
        }
        else
        {
            for( IniSection::iterator it = Sections[section].begin(); it != Sections[section].end(); ++it )
            {
                keys.push_back( it->first );
                count++;
            }
        }
    }

    return count;
}

//

bool Ini::MergeSections( const string& to, const string& from, bool overwrite /* = false */ )
{
    if( from == to || !IsSection( from ) )
        return false;

    vector<string> keys;
    for( unsigned int k = 0, kLen = GetSectionKeys( from, keys ); k < kLen; k++ )
    {
        if( overwrite || !IsSectionKey( to, keys[k] ) )
        {
            string key = keys[k];
            SetStr( to, key, Sections[from][key] );
        }
    }

    RemoveSection( from );
    return true;
}

bool Ini::RemoveSection( const string& section )
{
    if( !IsSection( section ) )
        return false;

    Sections.erase( section );

    RemoveSectionRaw( section );
    RemoveSectionOrder( section );

    return true;
}

//

bool Ini::IsSectionRaw( const string& section )
{
    return SectionsRaw.find( section ) != SectionsRaw.end();
}

vector<string> Ini::GetSectionRaw( const string& section )
{
    vector<string> result;

    if( IsSectionRaw( section ) )
        result = SectionsRaw[section];

    return result;
}

string Ini::GetSectionRawString( const string& section, const string& separator )
{
    string         result;

    bool           first = true;
    vector<string> raw = GetSectionRaw( section );
    for( auto it = raw.begin(); it != raw.end(); ++it )
    {
        if( first )
            first = false;
        else
            result += separator;

        result += *it;
    }

    return result;
}

void Ini::AddSectionRaw( const string& section, const string& line )
{
    if( line.empty() )
        return;

    if( !IsSectionRaw( section ) )
    {
        vector<string>& raw = SectionsRaw[section];
        raw.push_back( line );
    }
    else
        SectionsRaw[section].push_back( line );
}

bool Ini::RemoveSectionRaw( const string& section )
{
    if( !IsSectionRaw( section ) )
        return false;

    SectionsRaw.erase( section );

    return true;
}

//

bool Ini::IsSectionOrder( const string& section )
{
    return SectionsOrder.find( section ) != SectionsOrder.end();
}

void Ini::AddSectionOrder( const string& section, const string& key )
{
    if( !IsSectionOrder( section ) )
    {
        vector<string>& ini_section = SectionsOrder[section];
        ini_section.push_back( key );
    }
    else
        SectionsOrder[section].push_back( key );
}

bool Ini::RemoveSectionOrder( const string& section )
{
    if( !IsSectionOrder( section ) )
        return false;

    SectionsOrder.erase( section );

    return true;
}

//

bool Ini::GetBool( const string& section, const string& key, const bool& default_value )
{
    bool result = default_value;

    if( !IsSectionKeyEmpty( section, key ) )
    {
        string str = Sections[section][key];
        transform( str.begin(), str.end(), str.begin(), ::tolower );

        result = (str == "1" || str == "yes" || str == "true" || str == "on" || str == "enable");
    }

    return result;
}

int Ini::GetInt( const string& section, const string& key, const int& default_value, const unsigned char& base /* = 10 */ )
{
    int result = default_value;

    if( !IsSectionKeyEmpty( section, key ) )
    {
        string str = Sections[section][key];

        // https://stackoverflow.com/a/6154614
        const char* cstr = str.c_str();
        char*       end;
        long        l;
        errno = 0;
        l = strtol( cstr, &end, base );
        if( ( (errno == ERANGE && l == LONG_MAX) || l > INT_MAX ) ||
            ( (errno == ERANGE && l == LONG_MIN) || l < INT_MIN ) ||
            (*cstr == '\0' || *end != '\0') )
            result = default_value;
        else
            result = l;
    }

    return result;
}

int Ini::GetOct( const string& section, const string& key, const int& default_value )
{
    return GetInt( section, key, default_value, 8 );
}

int Ini::GetHex( const string& section, const string& key, const int& default_value )
{
    return GetInt( section, key, default_value, 16 );
}

string Ini::GetStr( const string& section, const string& key )
{
    if( !IsSectionKeyEmpty( section, key ) )
        return string( Sections[section][key] );

    static const string empty;
    return empty;
}

string Ini::GetStr( const string& section, const string& key, const string& default_value )
{
    if( !IsSectionKeyEmpty( section, key ) )
        return string( Sections[section][key] );

    return string( default_value );
}

vector<string> Ini::GetStrVec( const string& section, const string& key, char separator /* = ' ' */ )
{
    string         value = GetStr( section, key );
    vector<string> result;

    if( !value.empty() )
    {
        string        tmp;
        istringstream f( value );
        while( getline( f, tmp, separator ) )
        {
            Cleanup( tmp );
            if( separator != ' ' )
            {
                TrimLeft( tmp );
                TrimRight( tmp );
            }
            result.push_back( tmp );
        }
    }

    return result;
}

//

void Ini::SetStr( const string& section, const string& key, string value )
{
    if( IsSectionKey( section, key ) )
        Sections[section][key] = value;
    else
    {
        IniSection& ini_section = Sections[section];
        ini_section.insert( make_pair( key, value ) );
    }

    if( KeepKeysOrder )
        AddSectionOrder( section, key );
}
