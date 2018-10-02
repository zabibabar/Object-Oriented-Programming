#pragma once

#include "command.h"
#include <unordered_map>

class Decision : public Command
{

protected:
    vector <string> ifs;
public:
    Decision();
    Decision(string passage);
    void getifs();
    void findif(unordered_map < string, bool > &mapOfVars);
    int getsize();
    string getIndex(int);
};
