#pragma once
#include <map>

#include "parser.h"

using namespace std;

class codeGenerator {
public:
    string generate(programNode* root);
    string visitNode(node* nodeObj);
private:
    map<string, string> varTypes;
    map<string, string> varTypesDefaults;

    string visitProgram(programNode &node);
    string visitExpression(expressionNode &node);
    string visitAssignment(assignmentNode &node);
    string visitNumber(numberNode &node);
    string visitText(textNode &node);
    string visitBool(boolNode &node);
    string visitCall(callNode &node);
    string visitArithmaticOperator(arithmaticOperatorNode &node);
    string visitRelationalOperator(relationalOperatorNode &node);
    string visitIdentifier(identifierNode &node);
    string visitVariable(variableNode &node);
};
