#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

#include "command.h"


Command::Command(string body)
{
	commandText = body;
}
