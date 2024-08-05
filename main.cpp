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
    while (getline(file, line)) {
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
    } else
    {
        cerr << "Error opening file" << endl;
    }
}

int main()
{
    std::string filename = "C:/Programming/Gizmo/sourceCode/testSourceCode.giz";
    std::string fileContent = readGizFile(filename);

    // Tokenize, and output result
    lexer lex;
    vector<token> tokens = lex.tokenize(fileContent);
    for (auto token: tokens) {
        cout << "Token <-> " << TokenTypeStr[token.type] << " <-> " << token.value << "\n";
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
    cout << cppCode;
    writeCppToFile(cppCode, "C:/Programming/Gizmo/codeGenOut/main.cpp");

    return 0;
}
