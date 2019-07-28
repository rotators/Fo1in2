#include "ReDefine.h"

void ReDefine::InitOperators()
{
    Operators["Assign"] = ":=";
    Operators["Equals"] = "==";
    Operators["NotEquals"] = "!=";
    Operators["Lower"] = "<";
    Operators["LowerEquals"] = "<=";
    Operators["Greater"] = ">";
    Operators["GreaterEquals"] = ">=";
    Operators["Add"] = "+";
    Operators["AddEquals"] = "+=";
}

void ReDefine::FinishOperators()
{
    Operators.clear();
}

bool ReDefine::IsOperator( const std::string& op )
{
    return !GetOperatorName( op ).empty();
}

bool ReDefine::IsOperatorName( const std::string& opName )
{
    return Operators.find( opName ) != Operators.end();
}

std::string ReDefine::GetOperator( const std::string& op )
{
    auto it = Operators.find( op );
    if( it != Operators.end() )
        return it->second;

    return std::string();
}

std::string ReDefine::GetOperatorName( const std::string& op )
{
    for( auto it = Operators.begin(), end = Operators.end(); it != end; ++it )
    {
        if( it->second == op )
            return it->first;
    }

    return std::string();
}
