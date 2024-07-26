#include <iostream>
#include <string>

using namespace std;

string users[2][4] = {{"Ahmed", "0123", "21000", ""},
                      {"Noah",  "9876", "12500", ""}};

string login();

int username_index(const string &username);

string get_user_data(const string &username, char index);

int main_menu();

int input_number(const string &msg);

void edit_user_data(const string &username, const string &data, char index);

void check_balance(const string &username);

int main() {
    const string username = login();
    printf("Welcome, %s\n", username.c_str());
    while (true) {
        const int operation = main_menu();
        switch (operation) {
            case 0:
                check_balance(username);
                break;
            case 1:
                printf("%s", get_user_data(username, 3).c_str());
                break;
            case 2:
                break;
            default:
                printf("Good Bye, %s\n\n", username.c_str());
                return main();
        }
    }
}

string login() {
    string username, password;
    char counter = 0;
    do {
        printf("Enter your username:");
        cin >> username;
    } while (username_index(username) == -1);
    do {
        printf("You have %d trial/s to\nEnter your password:", 3 - counter);
        cin >> password;
        ++counter;
        if (password == get_user_data(username, 1))
            return username;
    } while (counter < 3);
    return login();
}

int username_index(const string &username) {
    int i = 0;
    for (const auto &user: users) {
        if (user[0] == username)
            return i;
        ++i;
    }
    return -1;
}

string get_user_data(const string &username, const char index) {
    return users[username_index(username)][index];
}

int main_menu() {
    const string operations[7] = {"Check Balance       ", "View Account History",
                                  "Withdraw Cash       ", "Deposit Cash        ",
                                  "Transfer Balance    ", "Check Balance       ",
                                  "Sign Out\n"};
    int operation;
    for (char i = 1; i < 8; ++i) {
        bool index = i % 2;
        string msg = (index ? "\n" : "");
        printf("%s[%d] %s", msg.c_str(), i, operations[i - 1].c_str());
    }
    do {
        operation = input_number("the number respective to the operation you want") - 1;
    } while (operation > 6);
    return operation;
}

int input_number(const string &msg) {
    string input;
    bool isInt = true;
    printf("Enter %s:", msg.c_str());
    cin >> input;
    for (char digit: input)
        if (!isdigit(digit))
            isInt = false;
    if (isInt)
        return stoi(input);
    else {
        printf("Please enter numbers only\n");
        return input_number(msg);
    }
}

void edit_user_data(const string &username, const string &data, const char index) {
    users[username_index(username)][index] = data;
}

void check_balance(const string &username) {
    printf("Your balance = %s\n", get_user_data(username, 2).c_str());
    const auto timeNow = time(nullptr);
    const string msg = "Checked Your Balance at " + string(ctime(&timeNow));
    edit_user_data(username, get_user_data(username, 3) + msg, 3);
}