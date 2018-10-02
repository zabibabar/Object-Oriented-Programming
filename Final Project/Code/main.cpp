#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>

using namespace std;

#include "fileparser.h"
#include "setcommand.h"
#include "command.h"
#include "decision.h"
#include "passage.h"
#include "links.h"

int main()
{
    unordered_map < string, bool > mapOfVars;
    int option;

    //FileParser html("display_test.html");
    //FileParser html("specialLink.html");
    //FileParser html("linkTest.html");
    FileParser html("if.html");
    if(html.fileNotFound())
    {
      cout << "File not found!" << endl;
    }


    html.findpassage();

    string name = html.getname(0);

    do {
        string passage = html.getpassage(name);
        Passage test (passage);
        test.display(mapOfVars, html);
        test.getOptions();

        cin >> option;

        while (option < 0 || option > test.vecSize())
        {
            cout << "try again" << endl;
            test.getOptions();
            cin >> option;
        }
        if (option > 0 && option <= test.vecSize())
        {
            name = test.getLink(option-1);
            cout << endl;
        }
    }
    while (option != 0);

}
