#include <fstream>
#include <iostream>
#include <regex>

#include "codeGenerator.h"
#include "lexer.h"
#include "parser.h"

using namespace std;

string readGizFile(const string& filename)
{
    ifstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    string decompressedData;
    string line;
    while (getline(file, line))
    {
        decompressedData.append(line);
    }

    std::regex pattern("\r");
    decompressedData = std::regex_replace(decompressedData, pattern, "\n");

    file.close();
    return decompressedData;
}

void writeCppToFile(const string& content, const string& filename) {
    ofstream outfile(filename);
    if (outfile.is_open())
    {
        outfile << content;
        outfile.close();
    }
    else
    {
        cerr << "Error opening file" << endl;
    }
}

void createCMakeLists(const string& filename)
{
    ofstream cmakeFile(filename);
    if (cmakeFile.is_open())
    {
        cmakeFile << "cmake_minimum_required(VERSION 3.28)\n";
        cmakeFile << "project(GizmoTest)\n";
        cmakeFile << "set(CMAKE_CXX_STANDARD 20)\n";
        cmakeFile << "add_executable(GizmoTest main.cpp)\n";
        cmakeFile.close();
    }
    else
    {
        cerr << "Error creating CMakeLists.txt" << endl;
    }
}

int main()
{
    string filename = "C:/Programming/Gizmo/sourceCode/testSourceCode.giz";
    string fileContent = readGizFile(filename);

    // Tokenize, and output result
    lexer lex;
    vector<token> tokens = lex.tokenize(fileContent);
    for (auto token: tokens)
    {
        cout << "Token <-> " << TokenTypeStr[token.type] << " <-> " << token.value << endl;
    }

    // Parse tokens
    parser par;
    programNode* root = par.parse(tokens);

    // Semantic analysis
    //TODO implement

    // Optimization
    //TODO implement

    // CodeGen
    codeGenerator codeGen;
    string cppCode = codeGen.generate(root);
    cout << "Code Gen Step: " << endl;
    cout << cppCode;
    writeCppToFile(cppCode, "C:/Programming/GizmoTest/main.cpp");
    createCMakeLists("C:/Programming/GizmoTest/CMakeLists.txt");

    return 0;
}
