#pragma once
using namespace std;

class ProjectExceptionSelect : exception
{

};
//SELECT(at_least_one_column, ...) | ALL FROM table_name[WHERE column_name = value]
class Select {
	string tableName = ""; //Table name
	int nrConditions = 0; //Number of conditons in the input, matrix
	char** conditions = nullptr; //Matrix with all words in the input
	int nrColumns = 0;  //number of columns to select
	char columns[20][200];  //columns to select
	bool formatType = 0; //=0 if there is no WHERE, 1 otherwise
	int values[200] = { 0 };
	int nrValues = 0;

public:
	//constructor
	Select() {

	}

	Select(string name) {
		this->setTableName(name);
	}

	Select(char** newInput, int newNrConditions) {
		this->setConditions(newInput, newNrConditions);
	}

	//copy constructor
	Select(const Select& s) {
		this->tableName = s.tableName;
		this->nrConditions = s.nrConditions;
		this->nrColumns = s.nrColumns;
		this->formatType = s.formatType;
		if (this->conditions != nullptr) {
			for (int i = 0; i < this->nrConditions; i++)
				delete[] this->conditions[i];
			delete[] this->conditions;
		}
		this->conditions = new char* [this->nrConditions];
		for (int i = 0; i < this->nrConditions; i++) {
			this->conditions[i] = new char[strlen(s.conditions[i]) + 1];
		}
		for (int i = 0; i < this->nrConditions; i++) {
			strcpy(this->conditions[i], s.conditions[i]);
		}
		for (int i = 0; i < nrColumns; i++) {
			strcpy(this->columns[i], s.columns[i]);
		}
	}

	
	//destructor
	~Select() {
		if (this->conditions != nullptr) {
			for (int i = 0; i < this->nrConditions; i++)
				delete[] this->conditions[i];
			delete[] this->conditions;
		}
	}

	void addInformation(char** newInput, int newNrWords) {
		if (_stricmp(newInput[0], "ALL") == 0 && _stricmp(newInput[1], "FROM") != 0)
		{
			throw new ProjectExceptionSelect();
		}
		//in columns stores all columns to be selected
		if (_stricmp(newInput[0], "ALL") == 0) {
			this->nrColumns = 1;
			strcpy(this->columns[0], newInput[0]);
		}
		else {
			this->nrColumns = 0;
			for (int i = 0; i < newNrWords && (_stricmp(newInput[i], "FROM") != 0); i++) {
				strcpy(this->columns[this->nrColumns], newInput[i]);
				this->nrColumns++;
			}
		}
		if (this->formatType == 1) {
			int i;
			for (i = 0; i < newNrWords && (_stricmp(newInput[i], "WHERE") != 0); i++){}
			this->nrConditions = 0;
			this->conditions = new char* [newNrWords - i];
			for (++i; i < newNrWords; i++) {
				this->conditions[this->nrConditions] = new char[strlen(newInput[i]) + 1];
				strcpy(this->conditions[this->nrConditions], newInput[i]);
				this->nrConditions++;
			}
		}
	}

	void startSelect() {
		this->getInfo();
	}

	void getInfo() {
		if (this->formatType == 0) {
			cout << endl << "Selects ";
			for (int i = 0; i < this->nrColumns; i++) {
				cout << this->columns[i] << " ";
			}
			cout << "columns from table " << this->tableName;
		}
		else {
			if (this->nrConditions != 2) {
				throw new ProjectExceptionSelect();
			}
			cout << endl << "Selects ";
			for (int i = 0; i < this->nrColumns; i++) {
				cout << columns[i] << " ";
			}
			cout << "columns from table " << this->tableName<<" where "<<this->conditions[0]<< " = "<<this->conditions[1];
		}
	}

	bool checkFormat(char** newInput, int newNrWords) {
		bool ok = false;
		int pozFrom = -1;
		for (int i = 0; i < newNrWords; i++) {
			if (_stricmp(newInput[i], "FROM") == 0) {
				ok = true;
				pozFrom = i;
			}
		}
		if (ok == false) {
			throw new ProjectExceptionSelect();
		}
		int pozWhere = -1;
		for (int i = 0; i < newNrWords; i++) {
			if (_stricmp(newInput[i], "WHERE") == 0) {
				formatType = 1;
				pozWhere = i;
			}
		}
		if (formatType == 1 && pozWhere - pozFrom != 2) {
			throw new ProjectExceptionSelect();
		}
		setTableName(string(newInput[pozFrom + 1]));
	}

	//setters getters
	string getTableName() {
		return this->tableName;
	}

	int getNrConditions() {
		return this->nrConditions;
	}

	char** getConditions() {
		return this->conditions;
	}

	int getNrColumns() {
		return this->nrColumns;
	}

	char* getColumns(int index) {
		if (index >= 0 && index < this->nrColumns) {
			return this->columns[index];
		}
		else {
			throw new ProjectExceptionSelect();
		}
	}

	bool getFormatType() {
		return this->formatType;
	}

	int getNrValues() {
		return this->nrValues;
	}

	int* getValues() {
		return this->values;
	}

	void setTableName(string name){
		if (name.length() > 0) {
			this->tableName = name;
		}
		else
		{
			throw new ProjectExceptionSelect();
		}
	}

	void setNrConditions(int nr) {
		if (nr > 0) {
			this->nrConditions = nr;
		}
		else
		{
			throw new ProjectExceptionSelect();
		}
	}

	void setConditions(char** newInput, int newNrConditions) {
		if (newInput != nullptr && newNrConditions > 0) {
			if (this->conditions != nullptr) {
				for (int i = 0; i < this->nrConditions; i++)
					delete[] this->conditions[i];
				delete[] this->conditions;
			}
			this->nrConditions = newNrConditions;
			this->conditions = new char* [this->nrConditions];
			for (int i = 0; i < this->nrConditions; i++) {
				this->conditions[i] = new char[strlen(newInput[i]) + 1];
			}
			for (int i = 0; i < this->nrConditions; i++) {
				strcpy(this->conditions[i], newInput[i]);
			}
		}
		else {
			throw new ProjectExceptionSelect();
		}
	}

	void setNrColumns(int nr) {
		if (nr > 0) {
			this->nrColumns = nr;
		}
		else
		{
			throw new ProjectExceptionSelect();
		}
	}

	void setColumns(char newInput[20][200], int newNrColumns) {
		if (newNrColumns > 0) {
			this->nrColumns = newNrColumns;
			for (int i = 0; i < this->nrColumns; i++) {
				strcpy(this->columns[i], newInput[i]);
			}
		}
		else
		{
			throw new ProjectExceptionSelect();
		}
	}

	void setFormatType(bool input) {
		this->formatType = input;
	}

	void setNrValues(int newNrValues) {
		if (newNrValues > 0) {
			this->nrValues = newNrValues;
		}
		else {
			throw new ProjectExceptionSelect();
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
			throw new ProjectExceptionSelect();
		}
	}

	//operators

	friend ostream& operator<<(ostream& output, const Select& s);

	Select operator=(const Select& s) {
		if (this != &s) {
			this->tableName = s.tableName;
			this->nrConditions = s.nrConditions;
			if (this->conditions != nullptr) {
				for (int i = 0; i < this->nrConditions; i++)
					delete[] this->conditions[i];
				delete[] this->conditions;
			}
			this->nrConditions = s.nrConditions;
			this->conditions = new char* [this->nrConditions];
			for (int i = 0; i < this->nrConditions; i++) {
				this->conditions[i] = new char[strlen(s.conditions[i]) + 1];
			}
			for (int i = 0; i < this->nrConditions; i++) {
				strcpy(this->conditions[i], s.conditions[i]);
			}
			this->nrColumns = s.nrColumns;
			for (int i = 0; i < this->nrColumns; i++) {
				strcpy(this->columns[i], s.columns[i]);
			}
			this->formatType = s.formatType;
			this->nrValues = s.nrValues;
			for (int i = 0; i < this->nrValues; i++) {
				this->values[i] = s.values[i];
			}
		}
		return *this;
	}

	char*& operator[](int);

	//adds another column to select
	void operator+(string name) {
		strcpy(this->columns[nrColumns], name.c_str());
		this->nrColumns++;
	}

	//deletes last column to be selected
	Select operator--(int) {
		Select s;
		s = *this;
		strcpy(this->columns[this->nrColumns-1],"");
		this->nrColumns--;
		return s;
	}

	Select operator--() {
		strcpy(this->columns[this->nrColumns - 1], "");
		this->nrColumns--;
		return *this;
	}

	explicit operator int() {
		return this->nrColumns;
	}

	Select operator!() {
		Select s = *this;
		char word[200];
		strcpy(word, s.tableName.c_str());
		for (int i = 0; i < strlen(word); i++) {
			if (word[i] >= 'a' && word[i] <= 'z') {
				word[i] = word[i] - 32;
			}
			else
				if (word[i] >= 'A' && word[i] <= 'Z') {
					word[i] = word[i] + 32;
				}
		}
		s.setTableName(string(word));
		return s;
	}

	//compares table names
	bool operator>(Select s) {
		char word1[200], word2[200];
		strcpy(word1, this->tableName.c_str());
		strcpy(word2, s.tableName.c_str());
		if (strcmp(word1, word2) == 1) {
			return 1;
		}
		return 0;
	}

	bool operator==(Select s) {
		char word1[200], word2[200];
		strcpy(word1, this->tableName.c_str());
		strcpy(word2, s.tableName.c_str());
		if (strcmp(word1, word2) == 0) {
			return 1;
		}
		return 0;
	}
};

char*& Select::operator[](int index) {
	if (index >= 0 && index < this->nrConditions) {
		return this->conditions[index];
	}
	else throw new ProjectExceptionSelect();
}

ostream& operator<<(ostream& output, const Select& s) {
	if (s.formatType == 0) {
		cout << endl << "Selects ";
		for (int i = 0; i < s.nrColumns; i++) {
			cout << s.columns[i] << " ";
		}
		cout << "columns from table " << s.tableName;
	}
	else {
		if (s.nrConditions != 2) {
			throw new ProjectExceptionSelect();
		}
		cout << endl << "Selects ";
		for (int i = 0; i < s.nrColumns; i++) {
			cout << s.columns[i] << " ";
		}
		cout << "columns from table " << s.tableName << " where " << s.conditions[0] << " = " << s.conditions[1];
	}
	return output;
}