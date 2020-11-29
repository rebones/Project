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
    try {
        CommandParser parse1("SELECT COL1 COL2 FROM TNAME WHERE A = B");
        parse1.startParse();
        //parse1.getInfo();
    }
    catch (ProjectExceptionParser* err) {
        cout << err->getError();
        delete err;
    }
}