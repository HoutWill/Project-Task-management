#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include <fstream>
#include <iomanip>
#include "Task.cpp"
#include "ImportantTask.cpp"
using namespace std;

class TaskManager {
private:
    vector<Task*> Tasks;

    // Helper function to validate date format
    bool validateDateFormat(const string& date) {
        regex datePattern(R"(^\d{2}/\d{2}/\d{4}$)");
        return regex_match(date, datePattern);
    }

public:
    void addTask() {
        char choice;
        do {
            string name, description, date, deadline;
            int priority;
            bool hasReminder;
            char useDeadline;

            cout << "Enter the name of the task: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter the description: ";
            getline(cin, description);

            // Date input with dd/mm/yyyy format
            while (true) {
                cout << "Enter the date (dd/mm/yyyy): ";
                getline(cin, date);
                if (validateDateFormat(date)) break;
                cout << "Invalid date format. Please enter the date in the format dd/mm/yyyy.\n";
            }

            cout << "Would you like to add a deadline for this task? (y/n): ";
            cin >> useDeadline;
            cin.ignore();

            if (tolower(useDeadline) == 'y') {
                while (true) {
                    cout << "Enter the deadline (dd/mm/yyyy): ";
                    getline(cin, deadline);
                    if (validateDateFormat(deadline)) break;
                    cout << "Invalid deadline format. Please enter the deadline in the format dd/mm/yyyy.\n";
                }
            } else {
                deadline = "No Deadline";
            }

            cout << "Enter the priority (number 1-99): ";
            while (!(cin >> priority)) {
                cin.clear();
                cin.ignore(10, '\n');
                cout << "Invalid input. Please enter a number for priority: ";
            }
            cin.ignore();

            cout << "Does this task have a reminder? (1 for Yes, 0 for No): ";
            while (!(cin >> hasReminder)) {
                cin.clear();
                cin.ignore(10, '\n');
                cout << "Invalid input. Please enter 1 (Yes) or 0 (No): ";
            }
            cin.ignore();

            Tasks.push_back(new ImportantTask(name, description, date, deadline, priority, hasReminder));
            cout << "Important task created successfully.\n";

            cout << "Do you want to add another task? (y/n): ";
            cin >> choice;
            cin.ignore();

        } while (tolower(choice) == 'y');

        if (tolower(choice) == 'n') {
            cout << "Exiting addTask.\n";
        }
    }

    void editTask() {
        if (Tasks.empty()) {
            cout << "No tasks available to edit.\n";
            return;
        }

        string name;
        cout << "Enter the name of the task you want to edit: ";
        cin.ignore();
        getline(cin, name);

        auto it = find_if(Tasks.begin(), Tasks.end(),
                          [&name](Task* task) { return task->getName() == name; });

        if (it != Tasks.end()) {
            Task* task = *it;
            int editChoice;

            cout << "What would you like to edit?\n";
            cout << "1. Name\n";
            cout << "2. Description\n";
            cout << "3. Date\n";
            cout << "4. Priority\n";

            ImportantTask* impTask = dynamic_cast<ImportantTask*>(task);
            if (impTask) {
                cout << "5. Deadline\n";
                cout << "6. Reminder\n";
            }

            cout << "0. Cancel\n";
            cout << "Enter your choice: ";
            cin >> editChoice;
            cin.ignore();

            switch (editChoice) {
                case 1: {
                    string newName;
                    cout << "Enter new name: ";
                    getline(cin, newName);
                    task->setName(newName);
                    break;
                }
                case 2: {
                    string newDescription;
                    cout << "Enter new description: ";
                    getline(cin, newDescription);
                    task->setDescription(newDescription);
                    break;
                }
                case 3: {
                    string newDate;
                    while (true) {
                        cout << "Enter new date (dd/mm/yyyy): ";
                        getline(cin, newDate);
                        if (validateDateFormat(newDate)) {
                            task->setDate(newDate);
                            break;
                        }
                        cout << "Invalid date format.\n";
                    }
                    break;
                }
                case 4: {
                    int newPriority;
                    cout << "Enter new priority: ";
                    cin >> newPriority;
                    cin.ignore();
                    task->setPriority(newPriority);
                    break;
                }
                case 5: {
                    if (impTask) {
                        string newDeadline;
                        while (true) {
                            cout << "Enter new deadline (dd/mm/yyyy): ";
                            getline(cin, newDeadline);
                            if (validateDateFormat(newDeadline)) {
                                impTask->setDeadline(newDeadline);
                                break;
                            }
                            cout << "Invalid deadline format.\n";
                        }
                    }
                    break;
                }
                case 6: {
                    if (impTask) {
                        bool newReminder;
                        cout << "Set reminder? (1 for Yes, 0 for No): ";
                        cin >> newReminder;
                        cin.ignore();
                        impTask->setReminder(newReminder);
                    }
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Invalid choice.\n";
            }

            cout << "Task updated successfully.\n";
        } else {
            cout << "Task with the name \"" << name << "\" not found.\n";
        }
    }

    void viewTask() {
        if (Tasks.empty()) {
            cout << "No tasks were found.\n";
            return;
        }

        cout << left
             << setw(20) << "Name"
             << setw(30) << "Description"
             << setw(15) << "Date"
             << setw(10) << "Priority"
             << setw(15) << "Deadline"
             << setw(10) << "Reminder"
             << endl;
        cout << string(85, '-') << endl;

        for (Task* task : Tasks) {
            task->displayInfo();
        }
    }

    void deleteTask() {
        if (Tasks.empty()) {
            cout << "No tasks available to delete.\n";
            return;
        }

        string name;
        cout << "Enter the name of the task you want to delete: ";
        cin.ignore();
        getline(cin, name);

        auto it = find_if(Tasks.begin(), Tasks.end(),
                          [&name](Task* task) { return task->getName() == name; });

        if (it != Tasks.end()) {
            char confirm;
            cout << "Are you sure you want to delete the task \"" << name << "\"? (y/n): ";
            cin >> confirm;

            if (tolower(confirm) == 'y') {
                delete *it;
                Tasks.erase(it);
                cout << "Task deleted successfully.\n";
            } else {
                cout << "Deletion cancelled.\n";
            }
        } else {
            cout << "Task with the name \"" << name << "\" not found.\n";
        }
    }

    void searchTask() {
        if (Tasks.empty()) {
            cout << "No tasks were found.\n";
            return;
        }

        string name;
        cout << "Enter the name of the task you want to search: ";
        cin.ignore();
        getline(cin, name);

        bool found = false;
        for (Task* task : Tasks) {
            if (task->getName() == name) {
                cout << left
                     << setw(20) << "Name"
                     << setw(30) << "Description"
                     << setw(15) << "Date"
                     << setw(10) << "Priority"
                     << setw(15) << "Deadline"
                     << setw(10) << "Reminder"
                     << endl;
                cout << string(85, '-') << endl;

                task->displayInfo();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "No task found with the name \"" << name << "\".\n";
        }
    }

    void sortTask() {
        if (Tasks.empty()) {
            cout << "No tasks available to sort.\n";
            return;
        }

        int sortChoice;
        cout << "Sort by:\n";
        cout << "1. Priority (Ascending)\n";
        cout << "2. Priority (Descending)\n";
        cout << "3. Name (Alphabetical)\n";
        cout << "4. Date\n";
        cout << "Enter your choice: ";
        cin >> sortChoice;
        cin.ignore();

        switch (sortChoice) {
            case 1:
                sort(Tasks.begin(), Tasks.end(),
                     [](Task* a, Task* b) { return a->getPriority() < b->getPriority(); });
                cout << "Tasks sorted by priority in ascending order.\n";
                break;
            case 2:
                sort(Tasks.begin(), Tasks.end(),
                     [](Task* a, Task* b) { return a->getPriority() > b->getPriority(); });
                cout << "Tasks sorted by priority in descending order.\n";
                break;
            case 3:
                sort(Tasks.begin(), Tasks.end(),
                     [](Task* a, Task* b) { return a->getName() < b->getName(); });
                cout << "Tasks sorted alphabetically by name.\n";
                break;
            case 4:
                sort(Tasks.begin(), Tasks.end(),
                     [](Task* a, Task* b) { return a->getDate() < b->getDate(); });
                cout << "Tasks sorted by date.\n";
                break;
            default:
                cout << "Invalid choice.\n";
                return;
        }
    }
    void saveTask() {
    string filename = "data.dat";
    string filePath = "../data/" + filename;
    
    ofstream file(filePath, ios::binary);
    if (!file) {
        throw runtime_error("Failed to open file for writing.");
    }

    // Save the number of tasks first
    size_t taskCount = Tasks.size();
    file.write(reinterpret_cast<const char*>(&taskCount), sizeof(taskCount));

    // Write each task's data
    for (const auto& task : Tasks) {
        // Write the entire task object
        file.write(reinterpret_cast<const char*>(task), sizeof(Task));
    }
    
    file.close();
    cout << "Tasks saved successfully to " << filePath << ".\n";
}

    ~TaskManager() {
        for (Task* task : Tasks) {
            delete task;
        }
        Tasks.clear();
    }
};
