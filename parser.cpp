#include "parser.h"

using namespace std;

programNode* parser::parse(vector<token> tokens)
{

    while (!tokens.empty())
    {
        int left = stoi(tokens.front().value);
        tokens.erase(tokens.begin());
        char op = tokens.front().value[0];
        tokens.erase(tokens.begin());
        int right = stoi(tokens.front().value);
        tokens.erase(tokens.begin());

        operatorNode* opNode = new operatorNode(op, new numberNode(left), new numberNode(right));
        programNode program = new programNode(opNode);
        return &program;
    }

    return nullptr;
}
