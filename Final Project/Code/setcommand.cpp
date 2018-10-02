#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctype.h>
#include <sstream>
#include <unordered_map>

using namespace std;

#include "setcommand.h"

SetCommand::SetCommand() : Command("")
{
}
SetCommand::SetCommand(string passage) : Command(passage)
{
}

void SetCommand::addVar(string varName, bool varVal, unordered_map < string, bool > &mapOfVars)
{
	mapOfVars.insert(pair<string, bool> (varName, varVal));
}

bool SetCommand::getVar(string varName, unordered_map < string, bool > &mapOfVars)
{
	return mapOfVars[varName];
}

void SetCommand::setVar(string varName, bool varVal, unordered_map < string, bool > &mapOfVars)
{
	mapOfVars[varName] = varVal;
}

void SetCommand::addToMap(unordered_map < string, bool > &mapOfVars)
{
	string tempName;
	bool tempVal = false;
	int nameIndex, nameEnd;
	string inputLine;
	const string command = "(set:";
	const string moneySign = "$";
	const string to = "to";
	istringstream input(commandText);
	//current position, implement later

	while(getline(input,inputLine))
	{
		int tempval2 = inputLine.find(command);

		if(inputLine.find(command) != string::npos)
		//while(inputLine.find(command) != string::npos)
		{

			//Saves index one space after finding moneysign
			//which signals beginning of var name
			nameIndex = inputLine.find(moneySign ) + 1;
			//Finds first space after the name location which signals
			//the end of the var name
			nameEnd = inputLine.find(" ", nameIndex);
			tempName = inputLine.substr(nameIndex, nameEnd - nameIndex);



            // Sets index two spaces after 'to' is found then iterates
            // Character by character until it finds either T or F
            // Which signals either true or false was found
			for(int i = (inputLine.find(to, nameEnd) + 2); i != '\0'; i++)
			{
				if(tolower(inputLine[i]) == 't')
				{
					tempVal = true;
					break;
				} else if (tolower(inputLine[i]) == 'f')
				{
					tempVal = false;
					break;
				}

			}
            //checking if they Var already exists. If it does, then it calls the set function.
			for(auto i : mapOfVars)
            {
                if (tempName == i.first)
                {
                    setVar(tempName, tempVal, mapOfVars);
                    continue;
                }

            }

				addVar(tempName,tempVal, mapOfVars);

		}
	}


}
