#pragma once
#include <string>
#include <vector>
#include "domain.h"
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <exception>
#include <sstream>

using namespace std;

class FileRepo {
private:
	vector<Task> all;

public:
	FileRepo() { readFile(); };

	void readFile();

	void writeFile();

	void addTask(Task& t);

	void golesteRepo();

	vector<Task> get_all();

	bool exist(int id);

	bool validare(Task& t);

	void modifyTask(Task& task, string state);


};

void testeRepo();
