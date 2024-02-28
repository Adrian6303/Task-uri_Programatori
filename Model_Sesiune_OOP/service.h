#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <exception>
#include "domain.h"
#include "repo.h"
#include "Observer.h"

class Service : public Observable 
{
private:
	FileRepo& repo;

public:
	Service(FileRepo& rep) :repo{rep} {}

	Service(const Service& ot) = delete;

	vector<Task> get_all();

	void addTask(int& id, string& desc, vector<string>& prog, string& stare);

	vector<Task> cauta_prog(string prog);

	vector<Task> filterByState(string stare);

	void modifyState(int id, string state);

};