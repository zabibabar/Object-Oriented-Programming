#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

#include "command.h"
#include "decision.h"

Decision::Decision() : ifs(), Command ("")
{
}

Decision::Decision(string passage) : ifs(), Command(passage)
{
}

void Decision::findif(unordered_map < string, bool > &mapOfVars)
{
    string str, parse;
    int a = 0;
    size_t b, c, d;

    istringstream iss;
    ostringstream oss(ostringstream::ate);

    iss.str(commandText);
    int e = 0;
    //cout << e++ << endl;

    while(getline(iss, str))
    {
        if (a == 0 && (b = str.find("(if:")) != string::npos)
        {
            string VarName, ifblock;
            bool VarVal = false;
            bool elif_VarVal = false;

            size_t locOfElse,locOfElseIf;
            size_t start = str.find("$") + 1;
            size_t over = str.find(" ", start);
            VarName = str.substr(start, over - start);

            size_t over1 = str.find(")", start) + 2;
            ifblock = str.substr(over, over1 - over);

            if (ifblock.find("true") != string::npos) VarVal = true;
            //cout << VarName << " " << mapOfVars[VarName] << " " << VarVal << endl;
            locOfElse = str.find("(else:", over1);
            locOfElseIf = str.find("(else-if:", over1);

            string elif_VarName, elif_ifblock;

            size_t elif_locOfElse;
            size_t elif_start = str.find("$", locOfElseIf) + 1;
            size_t elif_over = str.find(" ", elif_start);
            elif_VarName = str.substr(elif_start, elif_over - elif_start);

            size_t elif_over1 = str.find(")", elif_start) + 2;
            elif_ifblock = str.substr(elif_over, elif_over1 - elif_over);

            if (elif_ifblock.find("true") != string::npos) elif_VarVal = true;

            if (mapOfVars[VarName] == VarVal)
            {
                c = count(str.begin(), str.end(), '[');
                d = count(str.begin(), str.end(), ']');
                if(c == d)
                {
                    if(locOfElseIf == string::npos && locOfElse == string::npos)
                    {
                      parse = str.substr(over1, str.size()-over1-1);
                    }
                    else if(locOfElseIf != string::npos)
                        parse = str.substr(over1, locOfElseIf - over1 - 1);
                    else if(locOfElse != string::npos)
                        parse = str.substr(over1, locOfElse - over1 - 1);
                    else
                    {}

                    oss << parse;
                    parse = oss.str();
                    ifs.push_back(parse);
                    oss.str("");
                    a = c = d = 0;
                }
                else
                {
                    a++;
                    parse = str.substr(b);
                    oss << parse << endl;
                    continue;
                }
            }
            //* Implmenting Else If
            else if (mapOfVars[elif_VarName] == elif_VarVal && locOfElseIf != string::npos)
            {
              /*
              string elif_VarName, elif_ifblock;

              size_t elif_locOfElse;
              size_t elif_start = str.find("$", locOfElseIf) + 1;
              size_t elif_over = str.find(" ", elif_start);
              elif_VarName = str.substr(elif_start, elif_over - elif_start);
              cout << "Elif Var Name: " << elif_VarName << endl;

              size_t elif_over1 = str.find(")", elif_start) + 2;
              elif_ifblock = str.substr(elif_over, elif_over1 - elif_over);

              if (elif_ifblock.find("true") != string::npos) elif_VarVal = true;
              //*/

              if (mapOfVars[elif_VarName] == elif_VarVal)
              {
                  c = count(str.begin(), str.end(), '[');
                  d = count(str.begin(), str.end(), ']');
                  if(c == d)
                  {
                      if(locOfElse == string::npos)
                      {
                        parse = str.substr(elif_over1, str.size()-elif_over1-1);
                      }
                      else
                        parse = str.substr(elif_over1, locOfElse - elif_over1 - 1);

                      oss << parse;
                      parse = oss.str();
                      ifs.push_back(parse);
                      oss.str("");
                      a = c = d = 0;
                  }
                  else
                  {
                      a++;
                      parse = str.substr(b);
                      oss << parse << endl;
                      continue;
                  }
            }
          }
            //*///* Implmenting Else
            else if (mapOfVars[VarName] != VarVal && locOfElse != string::npos)
            {
              int openBracket, closeBracket;
              openBracket = str.find("[", locOfElse);
              closeBracket = str.find("]", openBracket);
              string elseBody = str.substr(openBracket + 1, closeBracket - openBracket - 1);
              oss << elseBody;
              parse = oss.str();
              ifs.push_back(parse);
              oss.str("");
              a = c = d = 0;
            }
            else
            {
              int x;
            }
            //*/

        if (a > 0)
        {
            c += count(str.begin(), str.end(), '[');
            d += count(str.begin(), str.end(), ']');
            //cout << c <<" " <<d << endl;
            if (c == d)
            {
                b = str.rfind("]");
                parse = str.substr(0, b+1);
                oss << parse;
                parse = oss.str();
                ifs.push_back(parse);
                oss.str("");
                a = c = d = 0;
            }
            else oss << str << endl;
        }

 }
}
}


void Decision::getifs()
{
    for (unsigned i = 0; i < ifs.size(); i++)
        {
            cout << ifs[i] << endl;
        }
}int Decision::getsize()
{
    return ifs.size();
}
string Decision::getIndex(int i)
{
    return ifs[i];
}
