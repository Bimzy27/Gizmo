#include <fstream>
#include <iostream>
#include <regex>

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

int main()
{
    std::string filename = "C:/Programming/Gizmo/sourceCode/testSourceCode.giz";
    std::string fileContent = readGizFile(filename);

    // Tokenize, and output result
    lexer lex;
    vector<token> tokens = lex.tokenize(fileContent);
    for (auto token: tokens) {
        cout << "Token - " << TokenTypeStr[token.type] << " - " << token.value << "\n";
    }

    // Parse tokens
    parser par;
    programNode* root = par.parse(tokens);

    // Semantic analysis
    //TODO implement

    // Optimization
    //TODO implement

    // CodeGen
    //TODO implement

    return 0;
}
