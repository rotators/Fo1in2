#ifndef __REDEFINE__
#define __REDEFINE__    // :)

#include <map>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

class Ini;

class ReDefine
{
public:

    typedef std::map<std::string, std::map<std::string, std::string>> GenericOperatorsMap;
    typedef std::map<std::string, std::vector<std::string>>           StringVectorMap;

    struct Function;
    struct Variable;

    //
    // ReDefine
    //

    Ini* Config;

    struct SStatus
    {
        struct SCurrent
        {
            std::string  File;
            std::string  Line;
            unsigned int LineNumber;

            SCurrent();
            void         Clear();
        }
        Current;

        struct SProcess
        {
            unsigned int                       Files;
            unsigned int                       FilesChanged;
            unsigned int                       Lines;
            unsigned int                       LinesChanged;

            std::map<std::string, std::string> Unknown;

            SProcess();
            void                               Clear();
        }
        Process;

        void Clear();
    }
    Status;

    ReDefine();
    virtual ~ReDefine();

    void Init();
    void Finish();

    void DEBUG( const char* func, const char* format, ... );
    void WARNING( const char* func, const char* format, ... );
    void LOG( const char* format, ... );
    void ILOG( const char* format, ... );

    bool ReadFile( const std::string& filename, std::vector<std::string>& lines );
    bool ReadConfig( const std::string& defines, const std::string& variable_prefix, const std::string& function_prefix, const std::string& raw );

    void ProcessHeaders( const std::string& path );
    void ProcessScripts( const std::string& path, const bool readOnly = false );


    //
    // Defines
    //

    struct Header
    {
        const std::string Filename;
        const std::string Type;
        const std::string Prefix;
        const std::string Group;

        Header( const std::string& filename, const std::string& type, const std::string& prefix, const std::string& group );
    };

    std::vector<Header>                               Headers;
    std::map<std::string, std::map<int, std::string>> RegularDefines; // <type, <value, define>>
    StringVectorMap                                   VirtualDefines; // <virtual_type, <types>>

    void FinishDefines();

    bool ReadConfigDefines( const std::string& section );

    bool IsDefineType( const std::string& type );
    bool GetDefineName( const std::string& type, const int value, std::string& result );

    bool ProcessHeader( const std::string& path, const Header& header );
    bool ProcessValue( const std::string& type, std::string& value, const bool silent = false );
    void ProcessValueGuessing( std::string& value );

    //
    // Functions
    //

    struct Function
    {
        std::string              Full; // Name + Arguments + (Operator + OperatorArguments)
        std::string              Name;
        std::vector<std::string> Arguments;
        std::string              Operator;
        std::string              OperatorArgument;

        unsigned int             ArgumentsEnd; // Name + Arguments only = Full.substr( 0, ArgumentsEndPos );

        Function( const std::string& full, const std::string& name, const std::vector<std::string>& arguments = std::vector<std::string>(), const std::string& op = std::string(), const std::string& opArgument = std::string() );
    };

    StringVectorMap     FunctionsArguments; // <name, <types>>
    GenericOperatorsMap FunctionsOperators; // <name, <operatorName, type>>

    void FinishFunctions();

    bool ReadConfigFunctions( const std::string& sectionPrefix );

    std::string GetFullString( const Function& function );

    void ProcessFunctionArguments( Function& current );

    //
    // Operators
    //

    std::map<std::string, std::string> Operators; // <operatorName, operator>

    void InitOperators();
    void FinishOperators();

    bool        IsOperator( const std::string& op );
    bool        IsOperatorName( const std::string& opName );
    std::string GetOperator( const std::string& opName );
    std::string GetOperatorName( const std::string& op );

    void ProcessOperator( const GenericOperatorsMap& map, const std::string& name, const std::string& op, std::string& opArgument );

    //
    // Raw
    //

    std::map<std::string, std::string> Raw;

    void FinishRaw();

    bool ReadConfigRaw( const std::string& section );

    //
    // Script.cpp
    //

    void ProcessScript( const std::string& path, const std::string& filename, const bool readOnly = false );

    //
    // Text
    //

    bool        TextIsComment( const std::string& text );
    bool        TextIsInt( const std::string& text );
    std::string TextGetFilename( const std::string& path, const std::string& filename );
    bool        TextGetInt( const std::string& text, int& result, const unsigned char& base = 10 );
    std::string TextGetJoined( const std::vector<std::string>& text, const std::string& delimeter );
    std::string TextGetLower( const std::string& text );
    std::string TextGetPacked( const std::string& text );
    std::string TextGetReplaced( const std::string& text, const std::string& from, const std::string& to );
    std::string TextGetTrimmed( const std::string& text );

    bool       TextIsDefine( const std::string& text );
    bool       TextGetDefine( const std::string& text, const std::regex& re, std::string& name, int& value );
    std::regex TextGetDefineRegex( const std::string& prefix, bool paren );

    std::vector<Variable> TextGetVariables( const std::string& text );
    std::vector<Function> TextGetFunctions( const std::string& text );

    //
    // Variables
    //

    struct Variable
    {
        std::string Full;              // Name + Operator + OperatorArgument
        std::string Name;
        std::string Operator;
        std::string OperatorArgument;

        Variable( const std::string& full, const std::string& name, const std::string& op, const std::string& opArgument );
    };

    GenericOperatorsMap      VariablesOperators; // <name, <operatorName, type>>
    std::vector<std::string> VariablesGuessing;  // <types>

    void FinishVariables();

    bool ReadConfigVariables( const std::string& sectionPrefix );

    std::string GetFullString( const Variable& variable );
};

#endif // __REDEFINE__ //
