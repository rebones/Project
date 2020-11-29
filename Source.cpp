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
        char input[200];
        //cin.get(input,200);
        string in;
        in = string(input);

        //CommandParser parse1(in);
        //CommandParser parse1("CREATE TABLE table_name (col1,integer,col2,float)");
        //CommandParser parse1("DROP TABLE table_name");
        //CommandParser parse1("DISPLAY TABLE table_name");
        //CommandParser parse1("CREATE INDEX index_name ON table_name column_name");
        //CommandParser parse1("DROP INDEX index_name");
        //CommandParser parse1("INSERT INTO table_name VALUES(val1,val2,val3)");
        CommandParser parse1("DELETE FROM table_name WHERE col_name = value");
        //CommandParser parse1("SELECT (col1,col2) FROM table_name WHERE col_name = value");
        //CommandParser parse1("SELECT (col1,col2) FROM table_name");
        //CommandParser parse1("UPDATE table_name SET column_name = value WHERE column_name = value");
        parse1.startParse();
    }
    catch (ProjectExceptionParser* err) {
        cout << err->getError();
        delete err;
    }
}