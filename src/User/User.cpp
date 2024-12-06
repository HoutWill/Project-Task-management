#include <iostream>
#include <string>

using namespace std;

enum class UserRole {
    ADMIN,
    USER
};

class User {
private:
    string username;
    string password;
    UserRole role;

public:
    User(const string& uname, const string& pwd, UserRole r)
        : username(uname), password(pwd), role(r) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    UserRole getRole() const { return role; }
    void setPassword(const string& newPassword) {
    password = newPassword;
}

    void setRole(UserRole newRole) {
        role = newRole;
    }


};