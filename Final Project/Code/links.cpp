#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "links.h"
#include "command.h"
#include "fileparser.h"
#include "passage.h"

using namespace std;

Links::Links() : passage("")
{
}

Links::Links(string pass): passage(pass)
{
}

void Links::findLinks()
{
    string str, parse;
    size_t b, c;
    int specialLinkLoc;
    string specialDisplayName;


    istringstream iss;
    ostringstream oss (ostringstream::ate);

    iss.str(passage);

    while(getline(iss, str))
    {
        if ((b = str.find("[[")) != string::npos)
        {
            c = str.find("]]", b);
            if((specialLinkLoc = str.find("-&gt;")) == string::npos)
            {
                parse = str.substr(b+2, (c) - (b+2)) ;
                parse = trim(parse);
                cout << '"'<< parse << '"' << endl;
            }
            else
            {
                parse = str.substr(specialLinkLoc+5, c - (specialLinkLoc+5));
                parse = trim(parse);
                cout << '"' << str.substr(b+2, (specialLinkLoc) - (b+2)) << '"' << endl;
            }

            links.push_back(parse);
        }
    }
}

string Links::sendLink()
{
    return links.back();
}

string Links::trim(string& toBeTrimmed)
{
  size_t firstSpace = toBeTrimmed.find_first_not_of(" ");
  if (firstSpace == string::npos)
  return "";
  // Added in case passge name is surrounded by quotes
  if(toBeTrimmed[firstSpace] == '"')
      firstSpace++;
  size_t lastSpace = toBeTrimmed.find_last_not_of(" ");
  if(toBeTrimmed[lastSpace] == '"')
      lastSpace++;
  return toBeTrimmed.substr(firstSpace, (lastSpace-firstSpace)+ 1);
}
