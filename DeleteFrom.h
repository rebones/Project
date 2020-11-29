#pragma once
using namespace std;
class ProjectExceptionDeleteFrom : exception
{

};

class DeleteFrom {
	string tableName = ""; //Table name
	char** input = nullptr; //Matrix with all words in the input
	int nrWords = 0; //Number of words in the input, matrix
	int values[200] = { 0 };
	int nrValues = 0;

public:
	DeleteFrom() {

	}

	DeleteFrom(char** newInput, int newNrWords) {
		constructAtributes(newInput, newNrWords);
	}
	void constructAtributes(char** newInput, int newNrWords) {
		this->nrWords = newNrWords - 4;
		this->tableName = string(newInput[0]);
		this->input = new char* [this->nrWords];
		newNrWords = newNrWords - 2;
		int nr = 0;
		for (int i = 2; i < newNrWords; i++) {
			this->input[nr] = new char[strlen(newInput[i])+1];
			nr++;
		}
		nr = 0;
		for (int i = 2; i < newNrWords; i++) {
			strcpy(this->input[nr], newInput[i]);
			nr++;
		}

	}

	DeleteFrom(string tableName) {
		this->setTableName(tableName);
	}

	//copy constructor
	DeleteFrom(const DeleteFrom& df) {
		this->tableName = df.tableName;
		this->nrWords = df.nrWords;
		if (this->input != nullptr) {
			for (int i = 0; i < this->nrWords; i++)
				delete[] this->input[i];
			delete[] this->input;
		}
		this->input = new char* [this->nrWords];
		for (int i = 0; i < this->nrWords; i++) {
			this->input[i] = new char[strlen(df.input[i]) + 1];
		}
		for (int i = 0; i < this->nrWords; i++) {
			strcpy(this->input[i], df.input[i]);
		}

		this->nrValues = df.nrValues;
		for (int i = 0; i < nrValues; i++) {
			this->values[i] = df.values[i];
		}
	}

	//destructor
	~DeleteFrom() {
		if (this->input != nullptr) {
			for (int i = 0; i < this->nrWords; i++)
				delete[] this->input[i];
			delete[] this->input;
		}
	}

	void startDelete() {
		if (this->nrWords == 2) {
			this->getInfo();
		}
		else {
			throw new ProjectExceptionDeleteFrom();
		}
	}

	//setters
	//getters
	void getInfo() {
		cout << endl << "From table " << this->tableName << " all information is deleted where column " << this->input[0] << " = " << this->input[1];
	}

	string getTableName() {
		return this->tableName;
	}

	char** getInput() {
		return this->input;
	}

	int getNrWords() {
		return this->nrWords;
	}

	int* getValues() {
		return this->values;
	}

	int getNrValues() {
		return this->nrValues;
	}

	void setTableName(string name) {
		if (name.length() > 0) {
			this->tableName = name;
		}
		else
		{
			throw new ProjectExceptionDeleteFrom();
		}
	}

	void setInput(char** newInput, int newNrWords) {
		if (newInput != nullptr && newNrWords > 0) {
			if (this->input != nullptr) {
				for (int i = 0; i < this->nrWords; i++)
					delete[] this->input[i];
				delete[] this->input;
			}
			this->nrWords = newNrWords;
			this->input = new char* [this->nrWords];
			for (int i = 0; i < this->nrWords; i++) {
				this->input[i] = new char[strlen(newInput[i]) + 1];
			}
			for (int i = 0; i < this->nrWords; i++) {
				strcpy(this->input[i], newInput[i]);
			}
		}
		else {
			throw new ProjectExceptionDeleteFrom();
		}
	}

	void setNrWords(int nrWords) {
		if (nrWords > 0) {
			this->nrWords = nrWords;
		}
		else {
			throw new ProjectExceptionDeleteFrom();
		}
	}

	void setValues(int newValues[200], int newNrValues) {
		if (newNrValues > 0) {
			this->nrValues = newNrValues;
			for (int i = 0; i < this->nrValues; i++) {
				values[i] = newValues[i];
			}
		}
		else {
			throw new ProjectExceptionDeleteFrom();
		}
	}

	void setNrValues(int newNrValues) {
		if (newNrValues > 0) {
			this->nrValues = newNrValues;
		}
		else {
			throw new ProjectExceptionDeleteFrom();
		}
	}

	//operators
	friend ostream& operator<<(ostream& output, const DeleteFrom& df);

	DeleteFrom operator=(const DeleteFrom& df) {
		if (this != &df) {
			this->tableName = df.tableName;
			this->nrWords = df.nrWords;
			if (this->input != nullptr) {
				for (int i = 0; i < this->nrWords; i++)
					delete[] this->input[i];
				delete[] this->input;
			}
			this->input = new char* [this->nrWords];
			for (int i = 0; i < this->nrWords; i++) {
				this->input[i] = new char[strlen(df.input[i]) + 1];
			}
			for (int i = 0; i < this->nrWords; i++) {
				strcpy(this->input[i], df.input[i]);
			}

			this->nrValues = df.nrValues;
			for (int i = 0; i < nrValues; i++) {
				this->values[i] = df.values[i];
			}
		}
		return *this;
	}

	char*& operator[](int);

	void operator+(string name) {
		this->setTableName(name);
	}

	DeleteFrom operator--(int) {
		DeleteFrom newDf = *this;
		for (int i = 0; i < this->nrWords; i++) {
			delete[] this->input[i];
		}
		delete[] this->input;
		this->input = nullptr;
		this->nrWords = 0;
		return newDf;
	}

	DeleteFrom operator--() {
		for (int i = 0; i < this->nrWords; i++) {
			delete[] this->input[i];
		}
		delete[] this->input;
		this->input = nullptr;
		this->nrWords = 0;
		return *this;
	}

	explicit operator int() {
		return this->nrWords;
	}

	DeleteFrom operator!() {
		DeleteFrom del = *this;
		char word[200];
		strcpy(word, del.tableName.c_str());
		for (int i = 0; i < strlen(word); i++) {
			if (word[i] >= 'a' && word[i] <= 'z') {
				word[i] = word[i] - 32;
			}
			else
				if (word[i] >= 'A' && word[i] <= 'Z') {
					word[i] = word[i] + 32;
				}
		}
		del.setTableName(string(word));
		return del;
	}

	//compares table names
	bool operator>(DeleteFrom df) {
		char word1[200],word2[200];
		strcpy(word1, this->tableName.c_str());
		strcpy(word2, df.tableName.c_str());
		if (_stricmp(word1, word2)==1) {
			return 1;
		}
		return 0;
	}

	bool operator==(DeleteFrom df) {
		char word1[200], word2[200];
		strcpy(word1, this->tableName.c_str());
		strcpy(word2, df.tableName.c_str());
		if (_stricmp(word1, word2) == 0) {
			return 1;
		}
		return 0;
	}
};

char*& DeleteFrom::operator[](int index) {
	if (index >= 0 && index < this->nrWords) {
		return this->input[index];
	}
	else throw new ProjectExceptionDeleteFrom();
}

ostream& operator<<(ostream& output, const DeleteFrom& df) {
	DeleteFrom df2=df;
	df2.startDelete();
	return output;
}
