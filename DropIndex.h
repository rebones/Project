#pragma once
using namespace std;

class ProjectExceptionDropIndex : exception
{

};

class DropIndex {
	string indexName = "";
public:
	DropIndex(string name) {
		this->indexName = name;
	}

	void startDropIndex(int nrWords) {
		if (nrWords == 3) {
			this->getInfo();
		}
		else {
			throw new ProjectExceptionDropIndex();
		}
	}

	void getInfo() {
		cout << endl << "Index with name " << this->indexName << " is dropped";
	}
};