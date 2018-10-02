#pragma once
#include "command.h"
#include "fileparser.h"
#include "passage.h"
using namespace std;

class Links: public FileParser
{
protected:
    vector <string> links;
    string passage;
public:
    Links();
    Links(string);
    void findLinks();
    string sendLink();
    string trim(string& toBeTrimmed);

};
