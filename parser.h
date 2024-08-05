#pragma once
#include "lexer.h"

using namespace std;

class node
{
public:
    virtual ~node(){}
};

class numberNode : public node
{
public:
    numberNode(int value_) : value(value_) {}

    int value;
};

class operatorNode : public node
{
public:
    operatorNode(char op_, node* left_, node* right_) : op(op_), left(left_), right(right_) {}

    char op;
    node* left;
    node* right;
};

class programNode : public node
{
public:
    programNode(node* start_) : start(start_) {}
    programNode() {}

    node* start;
};

class parser
{
public:
    programNode* parse(vector<token> tokens);
};