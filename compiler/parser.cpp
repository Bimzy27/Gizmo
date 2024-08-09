#include "parser.h"

#include <iostream>

using namespace std;

programNode* parser::parse(vector<token> tokens)
{
    programNode* program = new programNode();
    while (!tokens.empty())
    {
        if (tokens.front().type == TokenType::Variable)
        {
            string type = tokens.front().value;
            tokens.erase(tokens.begin());
            string name = tokens.front().value;
            tokens.erase(tokens.begin());

            if (tokens.front().type == TokenType::NewLine)
            {
                tokens.insert(tokens.begin(), token("0", TokenType::Number));
            }

            if (tokens.front().type == TokenType::Equals)
            {
                tokens.erase(tokens.begin());
            }

            if (tokens[1].type == TokenType::Operator)
            {
                int left = stoi(tokens.front().value);
                tokens.erase(tokens.begin());
                char op = tokens.front().value[0];
                tokens.erase(tokens.begin());
                int right = stoi(tokens.front().value);
                tokens.erase(tokens.begin());

                variableNode* variable = new variableNode(type, name);
                numberNode* leftNode = new numberNode(left);
                numberNode* rightNode = new numberNode(right);
                operatorNode* operation = new operatorNode(op, leftNode, rightNode);
                assignmentNode* assign = new assignmentNode(variable, operation);

                program->executions.push_back(assign);
            }
            else
            {
                int val = stoi(tokens.front().value);
                tokens.erase(tokens.begin());

                variableNode* variable = new variableNode(type, name);
                numberNode* number = new numberNode(val);
                assignmentNode* assign = new assignmentNode(variable, number);
                program->executions.push_back(assign);
            }

            continue;
        }

        if (tokens.front().type == TokenType::Call)
        {
            string name = tokens.front().value;
            tokens.erase(tokens.begin());
            tokens.erase(tokens.begin()); // consume (
            string varName = tokens.front().value;
            tokens.erase(tokens.begin());
            tokens.erase(tokens.begin()); // consume )
            callNode* call = new callNode(name, varName);

            program->executions.push_back(call);
            continue;
        }

        cout << "Unhandled Token <-> " << TokenTypeStr[tokens.front().type] << " <-> " << tokens.front().value << "\n";
        tokens.erase(tokens.begin());
    }
    return program;
}
