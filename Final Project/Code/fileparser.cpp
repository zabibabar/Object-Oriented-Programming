#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

#include "fileparser.h"

FileParser::FileParser() : filename("")
{
}

FileParser::FileParser(string file)
{
    filename = file;
}
void FileParser::findpassage()
{
    int a = 0;
    size_t b, c = 0;
    string str, name, parse;
    string str1 = "<tw-passagedata";
    string str2 = "name=";
    string str3 = "tags";
    string str4 = "</tw-passagedata>";
    string str5 = "&quot;";

    int l = str2.size()+1;

    ifstream file(filename);
    if(!file.is_open())
    {
      cout << "File not found!" << endl;
      fileNotFoundVar = true;
    }
    ostringstream oss (ostringstream::ate);

    while(getline(file, str))
    {

        while ((b = str.find(str5)) != string::npos)
        {
            str.replace(b,str5.size(),"\"");
        }

        if (str.find(str1) != string::npos)
        {
            a++;
            b = str.find(str2);
            c = str.find(str3);
            name = str.substr(b+l,(c-2)-(b+l));
            names.push_back(name);

            b = str.find(">");
            parse = str.substr(b+1);
            oss << parse;
            continue;
        }
        if (a > 0)
        {
            if ((b = str.find(str4)) != string::npos)
            {
                parse = str.substr(0, b);
                oss << parse;

                parse = oss.str();
                passages.push_back(parse);
                oss.str("");
                a = 0;
            }
            else
                oss << str << endl;
        }
    }
}
string FileParser::getname(int index)
{
    return names[index];
}

string FileParser::getpassage(string name)
{
    unsigned int i;
    for (i = 0; i < names.size(); i++)
    {
        if (names[i] == name)
            break;
    }
    return passages.at(i);
}
