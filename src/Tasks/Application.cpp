#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <string>
#include "TaskManager.cpp"
#include "../User/UserManager.cpp"
using namespace std;

class Application {
private: 
    int choice;
    TaskManager taskManager;
    UserManager userManager;

    void displayMainMenu() {
        cout << "\n-----Main Menu------\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "0. Exit\n";
        cout << "---------------------------\n";
    }

    void displayAdminMenu() {
        cout << "\n-----Admin Menu------\n";
        cout << "1. User Management\n";
        cout << "2. Task Management\n";
        cout << "0. Logout\n";
        cout << "---------------------------\n";
    }

    void displayUserMenu() {
        cout << "\n-----User Menu------\n";
        cout << "1. Task Management\n";
        cout << "0. Logout\n";
        cout << "---------------------------\n";
    }

    void handleTaskManagement() {
        do {
            cout << "\n-----Task Manager------\n";
            cout << "1. Add Task\n";
            cout << "2. Edit Task\n";
            cout << "3. View Task\n";
            cout << "4. Delete Task\n";
            cout << "5. Sort Task\n";
            cout << "6. Search Task\n";
            cout << "7. Save Task\n";
            cout << "0. Exit\n";
            cout << "---------------------------\n";
            cin >> choice;

            switch(choice) {
                case 1: taskManager.addTask(); break;
                case 2: taskManager.editTask(); break;
                case 3: taskManager.viewTask(); break;
                case 4: taskManager.deleteTask(); break;
                case 5: taskManager.sortTask(); break;
                case 6: taskManager.searchTask(); break;
                case 7: taskManager.saveTask(); break;
                case 0: return;
                default: cout << "Invalid choice\n";
            }
        } while(choice != 0);
    }

public: 
    void run() {
        try {
            do {
                displayMainMenu();
                cin >> choice;

                switch(choice) {
                    case 1: // Login
                        if (userManager.login()) {
                            User* currentUser = userManager.getCurrentUser();
                            if (currentUser->getRole() == UserRole::ADMIN) {
                                do {
                                    displayAdminMenu();
                                    cin >> choice;

                                    switch(choice) {
                                        case 1: userManager.displayUserManagement(); break;
                                        case 2: handleTaskManagement(); break;
                                        case 0: userManager.logout(); break;
                                        default: cout << "Invalid choice\n";
                                    }
                                } while(choice != 0);
                            } else { // User Role
                                do {
                                    displayUserMenu();
                                    cin >> choice;

                                    switch(choice) {
                                        case 1: handleTaskManagement(); break;
                                        case 0: userManager.logout(); break;
                                        default: cout << "Invalid choice\n";
                                    }
                                } while(choice != 0);
                            }
                        }
                        break;
                    case 2: // Register
                        userManager.registerUser();
                        break;
                    case 0: // Exit
                        cout << "Exiting....\n";
                        return;
                    default:
                        cout << "Invalid choice\n";
                }
            } while(true);
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
};