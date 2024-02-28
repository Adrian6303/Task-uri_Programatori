#pragma once
#include <string>
#include <vector>

using namespace std;

class Task {


public:
	Task(int i, string d, vector <string> prog, string s) :id{ i }, desc{ d }, programatori{ prog }, stare{ s } {}

	int get_id() const {
		return id;
	}
	string get_desc() const {
		return desc;
	}
	vector<string> get_prog() const {
		return programatori;
	}
	string get_stare() const {
		return stare;
	}

	void set_id(int val) {
		id = val;
	}
	void set_desc(string val) {
		desc = val;
	}
	void set_prog(vector<string> val) {
		programatori = val;
	}
	void set_stare(string& val) {
		stare = val;
	}

	bool operator==(const Task& other) const {
		return (id == other.id);
	}


private:
	int id;
	string desc;
	vector <string> programatori;
	string stare;

};