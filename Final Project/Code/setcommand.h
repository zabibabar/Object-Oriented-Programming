#pragma once

#include "command.h"
#include <unordered_map>
using namespace std;


class SetCommand : public Command
{

private:
	//unordered_map< string, bool> mapOfVars;
public:
    SetCommand();
	SetCommand(string);
	void addVar(string, bool, unordered_map < string, bool > &mapOfVars);
	void setVar(string, bool, unordered_map < string, bool > &mapOfVars);
	bool getVar(string, unordered_map < string, bool > &mapOfVars);
	void addToMap(unordered_map < string, bool > &mapOfVars);



};




