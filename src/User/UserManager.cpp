#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "User.cpp"
using namespace std;


class UserManager {
private:
    vector<User> users;
    User* currentUser;

public:
    UserManager() : currentUser(nullptr) {
        // Add default admin user
        users.emplace_back("admin", "admin123", UserRole::ADMIN);
    }

    bool registerUser() {
        string username, password;
        int roleChoice;

        cout << "\n-----Register User------\n";
        cout << "Enter username: ";
        cin >> username;

        // Check if username already exists
        if (findUser(username)) {
            cout << "Username already exists. Registration failed.\n";
            return false;
        }

        cout << "Enter password: ";
        cin >> password;

        cout << "Select Role:\n";
        cout << "1. Admin\n";
        cout << "2. User\n";
        cout << "Enter role choice: ";
        cin >> roleChoice;

        UserRole role;
        switch (roleChoice) {
            case 1: role = UserRole::ADMIN; break;
            case 2: role = UserRole::USER; break;
            default:
                cout << "Invalid role. Defaulting to User.\n";
                role = UserRole::USER;
        }

        users.emplace_back(username, password, role);
        cout << "User registered successfully!\n";
        return true;
    }

    bool login() {
        string username, password;

        cout << "\n-----Login------\n";
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (const auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                currentUser = const_cast<User*>(&user);
                return true;
            }
        }

        cout << "Invalid username or password.\n";
        return false;
    }

    bool findUser(const string& username) const {
        return any_of(users.begin(), users.end(),
            [&username](const User& user) { return user.getUsername() == username; });
    }

    User* getCurrentUser() { return currentUser; }

    void logout() {
        currentUser = nullptr;
        cout << "Logged out successfully.\n";
    }

    void displayUserManagement() {
        if (!currentUser || currentUser->getRole() != UserRole::ADMIN) {
            cout << "Access denied. Admin rights required.\n";
            return;
        }

        int choice;
        do {
            cout << "\n-----User Manager------\n";
            cout << "1. Add User \n";
            cout << "2. Edit User \n";
            cout << "3. View Users \n";
            cout << "4. Delete User \n";
            cout << "0. Exit \n";
            cout << "---------------------------\n";
            cin >> choice;

            switch (choice) {
                case 1: registerUser(); break;
                case 2: editUser(); break;
                case 3: viewUsers(); break;
                case 4: deleteUser(); break;
                case 0: break;
                default: cout << "Invalid choice\n";
            }
        } while (choice != 0);
    }
    
    void viewUsers() {
        if (!currentUser || currentUser->getRole() != UserRole::ADMIN) {
            cout << "Access denied. Admin rights required.\n";
            return;
        }

        if (users.empty()) {
            cout << "No users found.\n";
            return;
        }

        cout << "\n-----Registered Users-----\n";
        for (const auto& user : users) {
            cout << "Username: " << user.getUsername()
                 << ", Role: " << (user.getRole() == UserRole::ADMIN ? "Admin" : "User") << endl;
        }
    }
    void editUser() {
    // Check admin rights
    if (!currentUser || currentUser->getRole() != UserRole::ADMIN) {
        cout << "Access denied. Admin rights required.\n";
        return;
    }

    string username;
    cout << "Enter username to edit: ";
    cin >> username;

    // Find the user
    auto it = find_if(users.begin(), users.end(), 
        [&username](const User& user) { return user.getUsername() == username; });

    // Check if user exists
    if (it == users.end()) {
        cout << "User not found.\n";
        return;
    }

    // Prevent editing the default admin
    if (it->getUsername() == "admin" && currentUser->getUsername() != "admin") {
        cout << "Cannot edit the default admin account.\n";
        return;
    }

    // Edit menu
    int choice;
    do {
        cout << "\n-----Edit User: " << username << "------\n";
        cout << "1. Change Password\n";
        cout << "2. Change Role\n";
        cout << "0. Exit\n";
        cout << "---------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Change Password
                string newPassword;
                cout << "Enter new password: ";
                cin >> newPassword;
                
                // Update password for the user
                it->setPassword(newPassword);
                cout << "Password updated successfully.\n";
                break;
            }
            case 2: {
                // Change Role
                int roleChoice;
                cout << "Select New Role:\n";
                cout << "1. Admin\n";
                cout << "2. User\n";
                cout << "Enter role choice: ";
                cin >> roleChoice;

                UserRole newRole;
                switch (roleChoice) {
                    case 1: newRole = UserRole::ADMIN; break;
                    case 2: newRole = UserRole::USER; break;
                    default:
                        cout << "Invalid role. No changes made.\n";
                        continue;
                }

                // Update role for the user
                it->setRole(newRole);
                cout << "Role updated successfully.\n";
                break;
            }
            case 0:
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 0);
}
    void deleteUser() {
        if (!currentUser || currentUser->getRole() != UserRole::ADMIN) {
            cout << "Access denied. Admin rights required.\n";
            return;
        }

        string username;
        cout << "Enter username to delete: ";
        cin >> username;

        auto it = remove_if(users.begin(), users.end(),
            [&username](const User& user) { return user.getUsername() == username; });

        if (it != users.end()) {
            users.erase(it, users.end());
            cout << "User deleted successfully.\n";
        } else {
            cout << "User not found.\n";
        }
    }
};

