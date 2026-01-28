#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<functional>
using namespace std;

class User{
public:
    string Username;
    string Password;

    User(string u, string p){
        this->Username = u;
        this->Password = p;
    }
};

class Validator{
public:
    bool ValidateUserName(string &username){
        return username.length() >= 4;
    }

    bool ValidatePassword(string &password){
        return password.length() >= 8;
    }
};

class IUser{
public:
    virtual bool UserExists(string &username) = 0;
    virtual void SaveUser(User& user) = 0;
    virtual string GetPassword(string &username) = 0;
    virtual ~IUser() {}
};

class Interface : public IUser {
private:
    string filename = "users.txt";
public:
    bool UserExists(string &username) override {
        ifstream file(filename);
        string u, p;
        while(file >> u >> p){
            if(u == username){
                return true;
            }
        }
        return false;
    }

    void SaveUser(User& user) override {
        ofstream file(filename, ios::app);
        file << user.Username << " " << user.Password << endl;
    }

    string GetPassword(string &username) override {
        ifstream file(filename);
        string u, p;

        while(file >> u >> p){
            if(u == username){
                return p;
            }
        }
        return "";
    }

};

class AuthorService{
private:
    IUser* repository;
    Validator valid;

    string hashPassword(string &password){
        return to_string(hash<string>{} (password));
    }
public:
    AuthorService(IUser* repo){
        this->repository = repo;
    }

    void RegisterUser(string &username, string &password){
        if(!valid.ValidateUserName(username)){
            cout << "Username too short\n" << endl;
            return;
        }

        if(!valid.ValidatePassword(password)){
            cout << "Password too weak\n" << endl;
            return;
        }

        if(repository->UserExists(username)){
            cout << "Username already exists!\n" << endl;
            return ;
        }

        User user(username, hashPassword(password));
        repository->SaveUser(user);
        cout << "Registration Successfull\n" << endl;
    }

    void LoginUser(string &username, string &password){

        if(!repository->UserExists(username)){
            cout << "User not found!\n" << endl;
            return ;
        }

        string p = repository->GetPassword(username);
        if(p == hashPassword(password)){
            cout << "Login Successfully done!\n" << endl;
        }
        else{
            cout << "Wrong Password!\n" << endl;
        }
    }
};

int main(){
    Interface repo;
    AuthorService auth(&repo);

    int choice;
    string username, password;

    cout << "1. Register\n 2. Login\nChoice: ";
    cin >> choice;

    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;

    if(choice == 1){
        auth.RegisterUser(username, password);
    }
    else if(choice == 2){
        auth.LoginUser(username, password);
    }
    else{
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

