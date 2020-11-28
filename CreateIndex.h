#pragma once
using namespace std;

class ProjectExceptionCreateIndex : exception
{

};

class CreateIndex {
	char** input = nullptr; //Matrix with all words in the input
	int nrWords = 0; //Number of words in the input, matrix

public:
	//constructor
	CreateIndex(char** newInput, int newNrWords){
		this->nrWords = newNrWords - 2;
		this->input = new char* [this->nrWords];
		int nr = 0;
		for (int i = 0; i < this->nrWords; i++) {  //copies matrix of words into class atribute input
			if (_stricmp(newInput[i], "ON") != 0) {
				this->input[nr] = new char[strlen(newInput[i]) + 1];
				nr++;
			}
		}
		nr = 0;
		for (int i = 0; i < this->nrWords; i++) {
			if (_stricmp(newInput[i], "ON") != 0) {
				strcpy(this->input[nr], newInput[i]);
				nr++;
			}	
		}
		this->nrWords--;
	}

	//copy constructor
	CreateIndex(const CreateIndex& ci) {
		this->nrWords = ci.nrWords;
		if (this->input != nullptr) {
			for (int i = 0; i < this->nrWords; i++)
				delete[] this->input[i];
			delete[] this->input;
		}
		this->input = new char* [this->nrWords];
		for (int i = 0; i < this->nrWords; i++) {
				this->input[i] = new char[strlen(ci.input[i]) + 1];

		}
		for (int i = 0; i < this->nrWords; i++) {
			strcpy(this->input[i], ci.input[i]);

		}
		this->nrWords--;
	}

	//the destroyer
	~CreateIndex() {
		if (this->input != nullptr) {
			for (int i = 0; i < this->nrWords; i++)
				delete[] this->input[i];
			delete[] this->input;
		}
	}

	void startIndex() {
		//checks if we have only one column to index
		if (this->nrWords == 3) {
			getInfo();
		}
		else {
			throw new ProjectExceptionCreateIndex();
		}
	}

	void getInfo() {
		cout << endl << "Created index with name: " << this->input[0];
		cout << endl << "On table named: " << this->input[1];
		cout << endl << "On column named: " << this->input[2];
	}
};