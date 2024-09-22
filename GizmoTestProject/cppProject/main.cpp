#include <iostream>
#include <map>
using namespace std;
int main()
{
map<string, string> varTypes;
map<string, int> numberVars;
map<string, string> textVars;
map<string, bool> boolVars;
varTypes["num1"] = "number";
if (numberVars.find("num1") == numberVars.end())
{ numberVars["num1"] = 0; }
numberVars["num1"] = 420;
cout << numberVars["num1"] << endl;
varTypes["num2"] = "number";
if (numberVars.find("num2") == numberVars.end())
{ numberVars["num2"] = 0; }
numberVars["num2"] = 69;
if(true) {
cout << numberVars["num2"] << endl;
}
string input;
cin >> input;
return 0;
}
