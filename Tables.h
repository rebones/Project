#pragma once
using namespace std;

class Tables {
	string name="";  //table name
	char** columns=nullptr; //matrix with name of all columns
	char** dataTypes=nullptr; //matrix with data types of all columns
	int nrColumns = 0;  //number of columns
public:
	//creates table
	Tables(char** input, int noWords) {
		this->name.assign(input[0],strlen(input[0])); //stores table name into class attribute name
		this->columns = new char* [noWords / 2];  //copies info into the 2 matrixes, columns and dataTypes
		this->dataTypes = new char* [noWords / 2];
		this->nrColumns = noWords / 2;
		int nr = 0;
		for (int i = 1; i < noWords - 1; i = i + 2) {
			this->columns[nr] = new char[strlen(input[i]) + 1];
			strcpy(this->columns[nr], input[i]);
			nr++;
		}
		nr = 0;
		for (int i = 2; i < noWords; i = i + 2) {
			this->dataTypes[nr] = new char[strlen(input[i]) + 1];
			strcpy(this->dataTypes[nr], input[i]);
			nr++;
		}
	}
	
	//copy constructor
	Tables(const Tables& t) {
		this->name = t.name;
		if (this->columns != nullptr) {
			for (int i = 0; i < this->nrColumns; i++)
				delete[] this->columns[i];
			delete[] this->columns;
		}
		this->nrColumns = t.nrColumns;
		this->columns = new char* [t.nrColumns];
		for (int i = 0; i < t.nrColumns; i++) {
			this->columns[i] = new char[strlen(t.columns[i]) + 1];
		}
		for (int i = 0; i < t.nrColumns; i++) {
			strcpy(this->columns[i], t.columns[i]);
		}

		if (this->dataTypes != nullptr) {
			for (int i = 0; i < this->nrColumns; i++)
				delete[] this->dataTypes[i];
			delete[] this->dataTypes;
		}
		this->dataTypes = new char* [t.nrColumns];
		for (int i = 0; i < t.nrColumns; i++) {
			this->dataTypes[i] = new char[strlen(t.dataTypes[i]) + 1];
		}
		for (int i = 0; i < t.nrColumns; i++) {
			strcpy(this->dataTypes[i], t.dataTypes[i]);
		}
	}

	//the destructor
	~Tables() {
		if (this->columns != nullptr) {
			for (int i = 0; i < this->nrColumns; i++) {
				delete[] this->columns[i];
				delete[] this->dataTypes[i];
			}
			delete[] this->columns;
			delete[] this->dataTypes;
		}
	}
};