#pragma once
#include "parser.h"

using namespace std;

class codeGenerator {
public:
    string generate(programNode* root);
    string visitNode(node* nodeObj);
private:
    string visitProgram(programNode &node);
    string visitExpression(expressionNode &node);
    string visitAssignment(assignmentNode &node);
    string visitNumber(numberNode &node);
    string visitCall(callNode &node);
    string visitOperator(operatorNode &node);
    string visitIdentifier(identifierNode &node);
};
