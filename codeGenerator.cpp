#include "codeGenerator.h"

using namespace std;

string codeGenerator::generate(programNode *root)
{
    string code;
    code += visitProgram(root);
    return code;
}

string codeGenerator::visitProgram(const programNode &node)
{
    return
        "#include <iostream>\n"
        "using namespace std;\n"
        "int main()\n"
        "{\n"
            "cout << \"My created script was made\";\n"
            "return 0;\n"
        "}\n";
     //"int main()\n{\nreturn 0;\n}";
}
