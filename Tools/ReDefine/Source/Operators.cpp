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
    Operators["Plus"] = "+";
    Operators["PlusEquals"] = "+=";
    Operators["Minus"] = "-";
    Operators["MinusEquals"] = "-=";
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

void ReDefine::ProcessOperator( const ReDefine::GenericOperatorsMap& opMap, ScriptCode& code )
{
    auto itName = opMap.find( code.Name );
    if( itName == opMap.end() )
        return;

    if( !IsOperator( code.Operator ) )
        return;

    auto itOp = itName->second.find( GetOperatorName( code.Operator ) );
    if( itOp == itName->second.end() )
    {
        DEBUG( nullptr, "<%s> %s <%s>", code.Name.c_str(), code.Operator.c_str(), code.OperatorArgument.c_str() );
        return;
    }

    ProcessValue( itOp->second, code.OperatorArgument );
}
