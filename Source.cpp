#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include "CommandParser.h"
#include "Tables.h"
using namespace std;


int main()
{
    CommandParser parse1("CrEaTE table Nume (col1 int, col2 text, col3 date)");
    CommandParser parse2 = parse1;
    //parse2.getInfo();
    parse1.startParse();
}