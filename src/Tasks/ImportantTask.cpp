#include <iostream>
#include <iomanip>
#include <string>
#include "Task.cpp"

class ImportantTask : public Task {
private:
    string deadline;
    bool hasReminder;
public:
    ImportantTask(string name = "none", string description = "none", string date = "none", 
                  string deadline = "none", int priority = 0, bool hasReminder = false)
        : Task(name, description, date, priority), deadline(deadline), hasReminder(hasReminder) {}

    void setDeadline(const string& newDeadline) { deadline = newDeadline; }
    string getDeadline() const { return deadline; }

    void setReminder(bool reminder) { hasReminder = reminder; }
    bool getReminder() const { return hasReminder; }

    void displayInfo() const override {
        Task::displayInfo();
        cout << setw(15) << deadline 
             << setw(10) << (hasReminder ? "Yes" : "No") 
             << endl;
    }
};