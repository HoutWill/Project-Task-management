#pragma once

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Task {
protected:
    string name, description, date;
    int priority;

public:
    Task(string name = "none", string description = "none", string date = "none", int priority = 0)
        : name(name), description(description), date(date), priority(priority) {}

    string getName() const { return name; }
    string getDescription() const { return description; }
    string getDate() const { return date; }
    int getPriority() const { return priority; }

    void setName(const string& newName) { name = newName; }
    void setDescription(const string& newDescription) { description = newDescription; }
    void setDate(const string& newDate) { date = newDate; }
    void setPriority(int newPriority) { priority = newPriority; }

    virtual void displayInfo() const {
        cout << left 
             << setw(20) << name 
             << setw(30) << description 
             << setw(15) << date 
             << setw(10) << priority;
    }

    virtual ~Task() {}
};
