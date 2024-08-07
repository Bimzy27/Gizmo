#include "codeGenerator.h"

using namespace std;

string codeGenerator::generate(programNode *root)
{
    string code;
    code += visitProgram(*root);
    return code;
}

string codeGenerator::visitNode(node* nodeObj)
{
    string nodeType = nodeObj->getType();
    if (nodeType == "expression")
    {
        return visitExpression(static_cast<expressionNode&>(*nodeObj));
    }
    if (nodeType == "assignment")
    {
        return visitAssignment(static_cast<assignmentNode&>(*nodeObj));
    }
    if (nodeType == "number")
    {
        return visitNumber(static_cast<numberNode&>(*nodeObj));
    }
    if (nodeType == "call")
    {
        return visitCall(static_cast<callNode&>(*nodeObj));
    }
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
    code += "std::map<string, int> intVars;\n";

    while (!node.executions.empty())
    {
        code += visitNode(node.executions.front());
        node.executions.erase(node.executions.begin());
    }

    code += "return 0;\n";
    code += "}\n";
    return code;
}

string codeGenerator::visitExpression(expressionNode &node)
{
    string nodeType = node.func->getType();
    string code;
    code += visitNode(node.func);
    return code;
}

string codeGenerator::visitAssignment(assignmentNode &node)
{
    string code;
    if (node.variable->type == "int")
    {
        code += "if (intVars.find(\"" + node.variable->name + "\") == intVars.end())\n";
        code += "{ intVars[\"" + node.variable->name + "\"] = 0; }\n";
        code += "intVars[\"" + node.variable->name + "\"] = ";
        code += visitNode(node.operation->left);
        code += node.operation->op;
        code += visitNode(node.operation->right);
        code += ";\n";
    }
    return code;
}

string codeGenerator::visitNumber(numberNode &node)
{
    string code;
    code += to_string(node.value);
    return code;
}

string codeGenerator::visitCall(callNode &node)
{
    string code;
    if (node.name == "print")
    {
        code += "cout << intVars[\"" + node.varName + "\"] << endl;\n";
    }
    return code;
}
