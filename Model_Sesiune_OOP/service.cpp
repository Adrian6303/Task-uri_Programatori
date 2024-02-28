#include "service.h"

void Service::addTask(int& id, string& desc, vector<string>& prog, string& stare) {
	Task T(id, desc, prog, stare);
	repo.addTask(T);
	this->notify_all();
}

vector<Task> Service::cauta_prog(string prog) {
	vector<Task> all = repo.get_all();
	vector<Task> tasks;
	for (auto t : all) {
		for (auto p : t.get_prog()) {
			if (prog == p)
			{
				tasks.push_back(t);
				break;
			}


		}
	}
	return tasks;
}

vector<Task> Service::get_all() {
	return repo.get_all();
}


vector<Task> Service::filterByState(string stare)
{
    auto tasks = get_all();
    vector<Task> filtered;
    for (auto& task : tasks)
    {
        if (task.get_stare() == stare)
            filtered.push_back(task);
    }
    return filtered;
}

void Service::modifyState(int id, string state)
{
    auto tasks = repo.get_all();
    for (auto& task : tasks)
    {
        if (task.get_id() == id)
        {
            repo.modifyTask(task, state);
            this->notify_all();
            break;
        }
    }
}
