#include <iostream>
#include <string>

using namespace std;

const string users[2][2] = {{"Ahmed", "0123"},
                            {"Noah",  "9876"}};

string login();

bool confirm_user_data(const string &userData, bool index);

int main_menu();

int input_number(const string &msg);

int main() {
    const string username = login();
    if (!username.empty()) {
        while (true) {
            const int operation = main_menu();
            printf("User: %s, Operation: %d\n", username.c_str(), operation);
            break;
        }
    } else
        return main();
    return 0;
}

string login() {
    string username, password;
    char counter = 0;
    bool userPresentFlag;
    do {
        printf("You have %d trial/s to\nEnter your username:", 3 - counter);
        cin >> username;
        ++counter;
        userPresentFlag = confirm_user_data(username, false);
    } while (!userPresentFlag && counter < 3);
    if (userPresentFlag) {
        counter = 0;
        do {
            printf("You have %d trial/s to\nEnter your password:", 3 - counter);
            cin >> password;
            ++counter;
            if (confirm_user_data(password, true))
                return username;
        } while (counter < 3);
    }
    return "";
}

bool confirm_user_data(const string &userData, const bool index) {
    for (const auto &user: users)
        if (user[index] == userData)
            return true;
    return false;
}

int main_menu() {
    const string operations[7] = {"Check Balance            ", "View Transactions History",
                                  "Withdraw Cash            ", "Deposit Cash             ",
                                  "Transfer Balance         ", "Check Balance            ",
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