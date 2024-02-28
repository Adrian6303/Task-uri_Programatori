#include "repo.h"
using namespace std;


void FileRepo::readFile() {

	ifstream fin("C:\\Users\\adria\\source\\repos\\Model_Sesiune_OOP\\Model_Sesiune_OOP\\tasks.txt");
	
	all.clear();
	int id;
	string desc;
	vector <string> programatori;
	string stare;
	string s;
	while (fin >> id >> desc) {
		programatori.clear();
		while (fin >> s) {
			if (s != "open" && s != "closed" && s != "inprogress") {
				programatori.push_back(s);
			}
			else {
				stare = s;
				break;
			}
		}
		Task t(id,desc,programatori, stare);
		all.push_back(t);
		
	}
	fin.close();
	
}

void FileRepo::writeFile() {

	ofstream fout("C:\\Users\\adria\\source\\repos\\Model_Sesiune_OOP\\Model_Sesiune_OOP\\tasks.txt");
	
	for (auto task : all) {
		fout << task.get_id() << " " << task.get_desc() << " ";
		for (auto prog : task.get_prog()) {
			fout << prog << " ";
		}
		fout << task.get_stare()<<" \n";
	}
	fout.close();

}

void FileRepo::golesteRepo() {
	all.clear();
	writeFile();
}

void FileRepo::addTask(Task& t) {
	if (exist(t.get_id()) == false && validare(t) == true)
	{
		readFile();
		all.push_back(t);
		sort(all.begin(), all.end(), [](Task t1, Task t2) {return t1.get_stare() < t2.get_stare();});
		writeFile();
	}
	else {
		throw exception("Ceva");
	}
	

}

vector<Task> FileRepo::get_all() {
	//readFile();
	return all;
}

bool FileRepo::exist(int id) {
	for (auto t : all) {
		if (t.get_id() == id)
			return true;
	}
	return false;
}

bool FileRepo::validare(Task& t) {
	if (t.get_id() < 0)
		return false;
	if (t.get_desc().size() == 0)
		return false;
	if (t.get_prog().size() == 0)
		return false;
	if (t.get_stare() != "open" && t.get_stare() != "closed" && t.get_stare() != "inprogress")
		return false;
	return true;
}

void FileRepo::modifyTask(Task& task, string state)
{
	readFile();
	all.erase(std::remove(all.begin(), all.end(), task), all.end());
	writeFile();
	task.set_stare(state);
	addTask(task);
	writeFile();

}



void testeRepo() {
	FileRepo r;
	r.readFile();
	vector<Task> Tasks = r.get_all();
	assert(Tasks.size() == 3);
	assert(Tasks[2].get_id() == 2123);
	assert(Tasks[2].get_desc() == "ceva");
	assert(Tasks[2].get_prog()[0] == "Cioban");
	assert(Tasks[2].get_prog()[1] == "Tudorica");
	assert(Tasks[2].get_stare() == "open");
	assert(Tasks[0].get_id() == 672);

	try {
		r.addTask(Tasks[0]);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	
	r.readFile();
	vector<Task> Tasks2 = r.get_all();
	assert(Tasks2.size() == 3);
	
	
}

