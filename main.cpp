#include <fstream>
#include <iostream>
#include "compiler/gizCompiler.h"

using namespace std;

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

int main()
{
    string filePath = "C:/Programming/GizmoTestProject/project.gizmo";
    string fileContents = readFile(filePath);

    gizCompiler compiler;
    compiler.compile(fileContents);

    return 0;
}