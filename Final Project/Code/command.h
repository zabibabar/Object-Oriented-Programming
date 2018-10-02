 #pragma once

#include <unordered_map>
using namespace std;

//unordered_map < string, bool > mapOfVars;


class Command
{
	// Text to be parsed by whatever class inherits command
protected:
	string commandText;
	//vector <int> maps;
public:
    Command(string);

};

