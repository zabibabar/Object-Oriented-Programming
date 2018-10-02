#pragma once

#include <unordered_map>
using namespace std;

#include "command.h"
#include "decision.h"
#include "setcommand.h"
#include "fileparser.h"
//#include "links.h"

//class Passage : public Decision, public SetCommand, public FileParser
class Passage : public FileParser
{
private:
    string pName;
    vector <string> linksInpass;
    vector<string> vec;

public:
    Passage();
    Passage(string);
    void display(unordered_map < string, bool > &mapOfVars, FileParser& rawPassages);
    string getLink(int);
    int vecSize();
    void getOptions();
    string trim(string& str);
};
