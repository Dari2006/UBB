#pragma once
#include "Task.h"
#include <algorithm>
#include <fstream>
#include <sstream>
class Repo{
private:
	vector<Task> tasks;
	string filename;  //numele fisierului
	
public:
	//constructor cu parametri
	Repo(const string& nume) : filename{ nume } {
		loadFromFile(filename);
		//sortTasks();
	}
	//getteri
	const vector<Task>& getAll() const {
		return tasks;
	}


	vector<Task>& getall(){
		return tasks;
	}

	//metoda auxiliara pentru a mentine lista sortata
	void sortTasks() {
		sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){return a.getStare() > b.getStare();});
	}
	//metoda care scrie in fisier
	//param: file - string - numele fisierului in care scriem
	void saveToFile(const string& file) const;
	//metoda care citeste din fisier
	void loadFromFile(const string& file);

	//metoda adauga un task
	//param: t - Task - task-ul ce trebuie adaugat
	void add(const Task& t) {
		tasks.push_back(t);
		saveToFile(filename);
		tasks.clear();
		loadFromFile(filename);
	}
};

