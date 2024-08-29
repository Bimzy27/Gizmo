#include "gizCompiler.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

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

    regex pattern("\r");
    decompressedData = regex_replace(decompressedData, pattern, "\n");

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

string getLine(const string& text, int lines)
{
    if (lines <= 0)
    {
        return "";
    }

    istringstream iss(text);
    string line;

    // Discard the lines
    for (int i = 1; i < lines; i++)
    {
        getline(iss, line);
    }

    getline(iss, line);
    return line;
}

string extractProjectFileAttribute(const string& input)
{
    size_t start = input.find('=') + 1;
    return input.substr(start);
}

string replaceBackslashWithSlash(const string& input)
{
    string output;
    output.reserve(input.size()); // Reserve space for efficiency
    for (char c : input)
    {
        if (c == ' ')
        {
            continue;
        }

        if (c == '\\')
        {
            output += '/';
        }
        else
        {
            output += c;
        }
    }
    return output;
}

void logTokens(vector<token> &tokens)
{
    for (auto token: tokens)
    {
        if (token.value == "\n")
        {
            cout << "Token <-> " << TokenTypeStr[token.type] << endl;
        }
        else
        {
            cout << "Token <-> " << TokenTypeStr[token.type] << " <-> " << token.value << endl;
        }
    }
}

string readFile(const string& filePath)
{
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return ""; // Or handle the error differently
    }

    // Get the file size
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // Allocate memory for the file content
    string fileContent(fileSize, '\0');

    // Read the file content into the string
    file.read(&fileContent[0], fileSize);

    return fileContent;
}

void gizCompiler::compile(string projectFile)
{
    ofstream myfile;

    // Open the file for writing
    myfile.open("C:\\Programming\\GizmoLauncher\\GizmoLauncher\\bin\\Debug\\net8.0\\example.txt");

    // Check if the file was opened successfully
    if (myfile.is_open()) {
        // Write data to the file
        myfile << projectFile;

        // Close the file
        myfile.close();
        cout << "File created and written successfully.\n";
    } else {
        cout << "Unable to open file.\n";
    }


    /*string fileContents = readFile(projectFile);

    // Get Giz files
    string path = extractProjectFileAttribute(getLine(projectFile, 2));
    path = replaceBackslashWithSlash(path);
    cout << "Path: " << path << endl;
    string mainFile = extractProjectFileAttribute(getLine(projectFile, 3));
    mainFile = replaceBackslashWithSlash(mainFile);
    cout << "MainFile: " << mainFile << endl;
    string filename = path + "/" + mainFile;
    string fileContent = readGizFile(filename);

    // Tokenize, and output result
    lexer lex;
    vector<token> tokens = lex.tokenize(fileContent);
    logTokens(tokens);

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
    writeCppToFile(cppCode, path + "/build/main.cpp");
    createCMakeLists(path + "/build/CMakeLists.txt");

    cout << "Compile Success!" << endl;*/
}

#define EXPORTED_COMPILE_METHOD extern "C" __declspec(dllexport)

EXPORTED_COMPILE_METHOD
void Compile(string gizmoProjectPath)
{
    gizCompiler comp;
    comp.compile(gizmoProjectPath);
}
