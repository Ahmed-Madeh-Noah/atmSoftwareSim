#include <iostream>
#include <string>

using namespace std;

string users[2][4] = {{"Ahmed", "0123", "21000", ""},
                      {"Noah",  "9876", "12500", ""}};

string login();

int username_index(const string &username);

string get_user_data(const string &username, char index);

int main_menu(const string &username);

int input_number(string &msg);

void edit_user_data(const string &username, const string &data, char index);

void record(const string &username, const string &msg);

int main() {
    const string username = login(), constraints = "The amount must be a positive integer and made of the bills 50, 100, 200";
    string otherUser;
    int numInput;
    printf("Welcome, %s\n", username.c_str());
    while (true) {
        string msg;
        const int operation = main_menu(username);
        switch (operation) {
            case 0:
                printf("Your balance = %s\n", get_user_data(username, 2).c_str());
                break;
            case 1:
                printf("%s", get_user_data(username, 3).c_str());
                break;
            case 2:
                do {
                    if (!msg.empty())
                        printf(constraints.c_str());
                    numInput = input_number(msg);
                    msg = "withdraw";
                } while (numInput % 50 != 0);
                edit_user_data(username, '-' + to_string(numInput), 2);
                printf("Successfully withdrew %d pounds", numInput);
                break;
            case 3:
                do {
                    if (!msg.empty())
                        printf(constraints.c_str());
                    numInput = input_number(msg);
                    msg = "deposit";
                } while (numInput % 50 != 0);
                edit_user_data(username, to_string(numInput), 2);
                printf("Successfully deposited %d pounds", numInput);
                break;
            case 4:
                msg = "transfer";
                do {
                    printf("Enter the username you want to transfer the money to:");
                    cin >> otherUser;
                } while (username_index(otherUser) == -1);
                numInput = input_number(msg);
                edit_user_data(username, '-' + to_string(numInput), 2);
                edit_user_data(otherUser, to_string(numInput), 2);
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

int main_menu(const string &username) {
    const string operations[7] = {"Check Balance       ", "View Account History",
                                  "Withdraw Cash       ", "Deposit Cash        ",
                                  "Transfer Balance    ", "Change PIN          ",
                                  "Sign Out"};
    string printingMsg = "the number respective to the operation you want";
    int operation;
    for (char i = 1; i < 8; ++i) {
        string msg = (i % 2 ? "\n" : "");
        printf("%s[%d] %s", msg.c_str(), i, operations[i - 1].c_str());
    }
    printf("\n");
    do {
        operation = input_number(printingMsg) - 1;
    } while (operation > 6);
    record(username, operations[operation]);
    return operation;
}

int input_number(string &msg) {
    string input;
    bool isInt = true;
    if (msg == "withdraw" || msg == "deposit" || msg == "transfer")
        msg = "the amount you want to " + msg + "(at least 50 pounds and in 50, 100, and 200 bills)";
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
    if (index == 2)
        users[username_index(username)][index] = to_string(stoi(get_user_data(username, 2)) + stoi(data));
    else
        users[username_index(username)][index] = data;
}

void record(const string &username, const string &msg) {
    const auto timeNow = time(nullptr);
    const string printingMsg = '"' + msg + "\" at time: " + string(ctime(&timeNow));
    edit_user_data(username, get_user_data(username, 3) + printingMsg, 3);
}