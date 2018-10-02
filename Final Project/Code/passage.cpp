#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <unordered_map>

#include "passage.h"
#include "command.h"
#include "decision.h"
#include "setcommand.h"
#include "links.h"
#include "fileparser.h"

using namespace std;


Passage::Passage(): pName("")
{
}

Passage::Passage(string name)
{
    pName = name;
}

void Passage::display(unordered_map < string, bool > &mapOfVars, FileParser& rawPassages)
{

    string str, parse;
    int a = 0, c = 0;
    size_t b;

    istringstream iss;
    ostringstream oss (ostringstream::ate);

    iss.str(pName);

    while(getline(iss, str))
    {
        if ((b = str.find("(if:")) != string::npos)
        {
            Decision pass(str);
            pass.findif(mapOfVars);
            size_t j = pass.getsize();
            if(j > 0)
            {
                for (unsigned i = 0; i < j; i++)
                {
                    Passage nestedIfs(pass.getIndex(i));
                    nestedIfs.display(mapOfVars, rawPassages);
                    for(string name : nestedIfs.linksInpass)
                      vec.push_back(name);
                }
            }
            continue;
        }

        else if ((b = str.find("(set:")) != string::npos)
        {
            SetCommand test(str);
            test.addToMap(mapOfVars);

            continue;
        }
        else if ((b = str.find("[[")) != string::npos)
        {
            Links test(str);
            test.findLinks();
            vec.push_back(test.sendLink());
            //test.printLinks();

            a++;
            continue;
        }
        else if( (b = str.find("(display:") ) != string::npos  )
        {
            string name;
            int startName, endName;


            if( ( startName = str.find(":", b) + 1 ) != string::npos)
            {
              endName = str.find(")", startName);

              name = str.substr(startName , endName- startName);
              cout << "Name before trim: " << name << endl;
              name = trim(name);
              cout << "Display Trim Name: " << name << endl;
              string passage = rawPassages.getpassage(name);

              Passage displayCommandPassage(passage);
              displayCommandPassage.display(mapOfVars,rawPassages);

              if(displayCommandPassage.vecSize() > 0)
              {
                for( int i = 0; i < displayCommandPassage.vecSize(); i++)
                {
                    vec.push_back(displayCommandPassage.linksInpass[i] );
                }
              }
            }
            else
            {
            }
        }
        else
            cout << str << endl;

    }

    if (vec.size() > 0)
    {
        for (unsigned i = 0; i < vec.size(); i++)
            linksInpass.push_back(vec[i]);
    }
}
string Passage::getLink(int i)
{
    return linksInpass[i];
}

int Passage::vecSize()
{
    return linksInpass.size();
}

void Passage::getOptions()
{
    cout << endl <<  "Enter 0 to quit" << endl;
    for (unsigned i = 0; i < linksInpass.size(); i++)
    {
        cout << "Enter " << i+1 << " for " << linksInpass[i] << endl;
    }
}

string Passage::trim(string& toBeTrimmed)
{
  size_t firstSpace = toBeTrimmed.find_first_not_of(" ");
  if (firstSpace == string::npos)
  return "";
  // Added in case passge name is surrounded by quotes
  if(toBeTrimmed[firstSpace] == '"')
      firstSpace++;
  size_t lastSpace = toBeTrimmed.find_last_not_of(" ");
  if(toBeTrimmed[lastSpace] == '"')
      lastSpace--;
  return toBeTrimmed.substr(firstSpace, (lastSpace-firstSpace)+1);
}
