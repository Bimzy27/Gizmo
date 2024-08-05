#include <fstream>
#include <iostream>
#include <regex>

#include "lexer.h"

using namespace std;

string readGizFile(const string& filename)
{
    ifstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << std::endl;
        return "";
    }

    string decompressedData;
    string line;
    while (getline(file, line)) {
        decompressedData.append(line);
    }

    std::regex pattern("\r");
    decompressedData = std::regex_replace(decompressedData, pattern, " \n");

    file.close();
    return decompressedData;
}

int main()
{
    lexer lex;

    std::string filename = "C:/Programming/Gizmo/sourceCode/testSourceCode.giz";
    std::string fileContent = readGizFile(filename);
    cout << fileContent << "\n";

    // Tokenize, and output result
    vector<token> tokens = lex.tokenize(fileContent);
    for (auto token: tokens) {
        cout << "Token - " << token.type << " - " << token.value << "\n";
    }
    return 0;
}
