#include "codeGenerator.h"

#include <iostream>
#include <map>

using namespace std;

string codeGenerator::generate(programNode *root)
{
    varTypesDefaults["number"] = "0";
    varTypesDefaults["text"] = "\"\"";
    varTypesDefaults["bool"] = "false";

    string code;
    code += visitProgram(*root);
    return code;
}

string codeGenerator::visitNode(node* nodeObj)
{
    string nodeType = nodeObj->getType();
    cout << "Visiting Node: " << nodeType << endl;
    if (nodeType == "expression")
    {
        return visitExpression(dynamic_cast<expressionNode&>(*nodeObj));
    }
    if (nodeType == "variable")
    {
        return visitVariable(dynamic_cast<variableNode&>(*nodeObj));
    }
    if (nodeType == "assignment")
    {
        return visitAssignment(dynamic_cast<assignmentNode&>(*nodeObj));
    }
    if (nodeType == "number")
    {
        return visitNumber(dynamic_cast<numberNode&>(*nodeObj));
    }
    if (nodeType == "text")
    {
        return visitText(dynamic_cast<textNode&>(*nodeObj));
    }
    if (nodeType == "bool")
    {
        return visitBool(dynamic_cast<boolNode&>(*nodeObj));
    }
    if (nodeType == "call")
    {
        return visitCall(dynamic_cast<callNode&>(*nodeObj));
    }
    if (nodeType == "arithmaticOperator")
    {
        return visitArithmaticOperator(dynamic_cast<arithmaticOperatorNode&>(*nodeObj));
    }
    if (nodeType == "relationalOperator")
    {
        return visitRelationalOperator(dynamic_cast<relationalOperatorNode&>(*nodeObj));
    }
    if (nodeType == "logicOperator")
    {
        return visitLogicOperator(dynamic_cast<logicOperatorNode&>(*nodeObj));
    }
    if (nodeType == "identifier")
    {
        return visitIdentifier(dynamic_cast<identifierNode&>(*nodeObj));
    }
    if (nodeType == "conditionalStatement")
    {
        return visitConditionalStatement(dynamic_cast<conditionalStatementNode&>(*nodeObj));
    }
    cout << "Unhandled node visisted of type: " << nodeObj->getType() << endl;
    return "";
}

string codeGenerator::visitProgram(programNode &node)
{
    string code;
    code += "#include <iostream>\n";
    code += "#include <map>\n";
    code += "using namespace std;\n";
    code += "int main()\n";
    code += "{\n";
    code += "map<string, string> varTypes;\n";
    code += "map<string, int> numberVars;\n";
    code += "map<string, string> textVars;\n";
    code += "map<string, bool> boolVars;\n";

    while (!node.executions.empty())
    {
        code += visitNode(node.executions.front());
        node.executions.erase(node.executions.begin());
    }
    
    code += "string input;\n";
    code += "cin >> input;\n";
    code += "return 0;\n";
    code += "}\n";
    return code;
}

string codeGenerator::visitExpression(expressionNode &node)
{
    string code;
    code += visitNode(node.func);
    return code;
}

string codeGenerator::visitAssignment(assignmentNode &node)
{
    string code;
    code += varTypes[node.varName->name] + "Vars[\"" + node.varName->name + "\"] = ";

    while (!node.assignments.empty())
    {
        code += visitNode(node.assignments.front());
        node.assignments.erase(node.assignments.begin());
    }

    code += ";\n";
    return code;
}

string codeGenerator::visitNumber(numberNode &node)
{
    string code;
    code += to_string(node.value);
    return code;
}

string codeGenerator::visitText(textNode &node)
{
    string code;
    code += node.value;
    return code;
}

string codeGenerator::visitBool(boolNode &node)
{
    string code;
    if (node.value)
    {
        code += "true";
    }
    else
    {
        code += "false";
    }
    return code;
}

string codeGenerator::visitCall(callNode &node)
{
    string code;
    if (node.name == "write")
    {
        code += "cout << " + varTypes[node.varName] + "Vars[\"" + node.varName + "\"];\n";
    }
    else if (node.name == "writeLine")
    {
        code += "cout << " + varTypes[node.varName] + "Vars[\"" + node.varName + "\"] << endl;\n";
    }
    return code;
}

string codeGenerator::visitArithmaticOperator(arithmaticOperatorNode &node)
{
    string code;
    code += visitNode(node.left);
    code += node.op;
    code += visitNode(node.right);
    return code;
}

string codeGenerator::visitRelationalOperator(relationalOperatorNode &node)
{
    string code;
    code += visitNode(node.left);
    code += node.op;
    code += visitNode(node.right);
    return code;
}

string codeGenerator::visitLogicOperator(logicOperatorNode &node)
{
    string code;
    if (node.op == "or")
    {
        code += "||";
    }
    else if (node.op == "and")
    {
        code += "&&";
    }
    return code;
}

string codeGenerator::visitIdentifier(identifierNode &node)
{
    string code;
    code += varTypes[node.name] + "Vars[\"" + node.name + "\"]";
    return code;
}

string codeGenerator::visitVariable(variableNode &node)
{
    varTypes[node.name] = node.type;
    string code;
    code += "varTypes[\"" + node.name + "\"] = \"" + node.type + "\";\n";
    code += "if (" + node.type + "Vars.find(\"" + node.name + "\") == " + node.type + "Vars.end())\n";
    code += "{ " + node.type + "Vars[\"" + node.name + "\"] = " + varTypesDefaults[node.type] + "; }\n";
    return code;

}

string codeGenerator::visitConditionalStatement(conditionalStatementNode& node)
{
    string code;
    if (node.conditionType == "if")
    {
        code += "if(true) {\n";
    }
    else if (node.conditionType == "else if")
    {
        code += "else if(true) {\n";
    }
    else if (node.conditionType == "else")
    {
        code += "else {\n";
    }
    while (!node.nested.empty())
    {
        code += visitNode(node.nested.front());
        node.nested.erase(node.nested.begin());
    }
    code += "}\n";
    return code;
}
