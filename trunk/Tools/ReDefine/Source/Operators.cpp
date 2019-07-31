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
    for( const auto& opName : Operators )
    {
        if( opName.second == op )
            return opName.first;
    }

    return std::string();
}

//

void ReDefine::ProcessOperator( const ReDefine::GenericOperatorsMap& opMap, const std::string& name, const std::string& op, std::string& opArgument )
{
    auto itName = opMap.find( name );
    if( itName == opMap.end() )
        return;

    if( !IsOperator( op ) )
        return;

    auto itOp = itName->second.find( GetOperatorName( op ) );
    if( itOp == itName->second.end() )
    {
        DEBUG( nullptr, "<%s> %s <%s>", name.c_str(), op.c_str(), opArgument.c_str() );
        return;
    }

    ProcessValue( itOp->second, opArgument );
}
