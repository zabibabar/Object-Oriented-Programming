#pragma once
class FileParser
{
private:
    vector <string> passages;
    vector <string> names;
    string filename;
    bool fileNotFoundVar = false;

public:
    FileParser();
    FileParser(string);
    void findpassage();
    string getname(int);
    string getpassage(string);
    bool fileNotFound(){return fileNotFoundVar;}
};
