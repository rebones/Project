#pragma once
#include "CreateTable.h"
using namespace std;

class ProjectExceptionParser : exception
{

};

//vector<string> commands = { "Create Table" };

class CommandParser
{
    string reader= "";  //Receives input from console
    char** input=nullptr; //Matrix with all words in the input
    int nrWords = 0;  //Number of words in the input, matrix
    //CreateTable tables[100];

    const static int INPUT_LENGHT_MAX = 200;
public:
    //constructor, gets command from console
    CommandParser(string word)
    {
        if (word.length() > 0 && word.length() < INPUT_LENGHT_MAX)  //checks lenght of input from conole
        {
            char input[INPUT_LENGHT_MAX];
            this->reader += word;
            strcpy(input, this->reader.c_str()); 
            char cuv[20][INPUT_LENGHT_MAX];       //makes matrix of words
            char* p;
            p = strtok(input, " (),");
            while (p != NULL)
            {
                strcpy(cuv[this->nrWords], p);
                this->nrWords++;
                p = strtok(NULL, " (),");
            }
            
            this->input = new char* [this->nrWords];  //copies matrix of words into class atribute input
            for (int i = 0; i < this->nrWords; i++) {
                this->input[i] = new char[strlen(cuv[i]) + 1];
            }
            for (int i = 0; i < this->nrWords; i++) {
                strcpy(this->input[i], cuv[i]);
            }
        }
        else
        {
            throw new ProjectExceptionParser();
        }
    }

    //copy constructor
    CommandParser(const CommandParser& cp) {
        this->reader = cp.reader;
        this->nrWords = cp.nrWords;
        if (this->input != nullptr) {
            for (int i = 0; i < this->nrWords; i++)
                delete[] this->input[i];
            delete[] this->input;
        }
        this->input = new char* [this->nrWords];
        for (int i = 0; i < this->nrWords; i++) {
            this->input[i] = new char[strlen(cp.input[i]) + 1];
        }
        for (int i = 0; i < this->nrWords; i++) {
            strcpy(this->input[i], cp.input[i]);
        }
    }
    
    //the destroyer
    ~CommandParser() {
        if (this->input != nullptr) {
            for (int i = 0; i < this->nrWords; i++)
                delete[] this->input[i];
            delete[] this->input;
        }
    }

    //starts to parse input
    void startParse() {
        if ((_stricmp(this->input[0], "CREATE") == 0) && (_stricmp(this->input[1], "TABLE") == 0)) {
            CreateTable create(this->input+2, this->nrWords);
            create.startCreate();
        }
    }

    void getInfo()
    {
        cout <<this->reader<<endl;
        for (int i = 0; i < this->nrWords; i++) {
            cout << this->input[i]<< endl;
        }
        cout << this->nrWords;
    }
};
