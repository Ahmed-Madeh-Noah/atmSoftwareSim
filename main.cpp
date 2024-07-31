#include <iostream>
#include <string>

using namespace std;

string users[2][4] = {{"Ahmed", "0123", "21000", ""},
                      {"Noah",  "9876", "12500", ""}};

string login();

int username_index(const string &username);

string get_user_data(const string &username, char index);

int main_menu();

int input_number(string &msg);

void edit_user_data(const string &username, const string &data, char index);

void record(const string &username, const int &index = 0, int amount = 0, const string &otherUser = "");

void withdraw_cash(const string &username);

void deposit_cash(const string &username);

void transfer_balance(const string &username);

void change_pin(const string &username);

int main() {
    const string username = login();
    string otherUser;
    int numInput;
    printf("Welcome, %s\n", username.c_str());
    while (true) {
        string msg;
        const int operation = main_menu();
        switch (operation) {
            case 0:
                numInput = stoi(get_user_data(username, 2));
                record(username, operation, numInput);
                break;
            case 1:
                printf(get_user_data(username, 3).c_str());
                record(username, operation);
                break;
            case 2:
                withdraw_cash(username);
                record(username, operation, numInput);
                break;
            case 3:
                deposit_cash(username);
                record(username, operation, numInput);
                break;
            case 4:
                transfer_balance(username);
                record(username, operation, numInput, otherUser);
                break;
            case 5:
                change_pin(username);
                record(username, operation);
                break;
            default:
                printf("Good Bye, %s\n\n", username.c_str());
                return main();
        }
    }
}

string login() {
    string username, password;
    int counter = 0;
    do {
        printf("Enter your username:");
        cin >> username;
    } while (username_index(username) == -1);
    do {
        printf("You have %d to enter your password\nEnter your password:", 3 - counter);
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
                                  "Transfer Balance    ", "Change PIN          ",
                                  "Sign Out"};
    string printingMsg = "the number respective to the operation you want";
    int operation = 0;
    for (char i = 1; i < 8; ++i) {
        string msg = (i % 2 ? "\n" : "");
        printf("%s[%d] %s", msg.c_str(), i, operations[i - 1].c_str());
    }
    printf("\n");
    do {
        if (operation == -1 || operation > 6)
            printf("The choice value must be respective to an operation\n");
        operation = input_number(printingMsg) - 1;
    } while (operation == -1 || operation > 6);
    return operation;
}

int input_number(string &msg) {
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
    if (index == 2)
        users[username_index(username)][index] = to_string(stoi(get_user_data(username, 2)) + stoi(data));
    else
        users[username_index(username)][index] = data;
}

void record(const string &username, const int &index, const int amount, const string &otherUser) {
    auto timeNow = time(nullptr);
    const string time = " at: " + string(ctime(&timeNow));
    const string amountStr = to_string(amount) + " Pounds";
    string msg;
    switch (index) {
        case 1:
            msg = "Viewed your account history" + time;
            break;
        case 2:
            msg = "Withdrew " + amountStr + " from your account" + time;
            break;
        case 3:
            msg = "Deposited " + amountStr + " to your account" + time;
            break;
        case 4:
            msg = "Transferred " + amountStr + " from your account balance to " + otherUser + time;
            break;
        case 5:
            msg = "Changed your PIN" + time;
            break;
        default:
            msg = "Checked balance and it was: " + amountStr + time;
    }
    printf(msg.c_str());
    edit_user_data(username, get_user_data(username, 3) + msg, 3);
}

void withdraw_cash(const string &username) {
    string msg;
    int numInput;
    bool haveMoney;
    do {
        if (!msg.empty())
            printf("The amount must be of bills 50, 100, 200\n");
        msg = "the amount you want to withdraw";
        numInput = input_number(msg);
        haveMoney = stoi(get_user_data(username, 2)) >= numInput;
        if (!haveMoney)
            printf("The amount you want to withdraw is larger than what you have in your account\n");
    } while (numInput % 50 != 0 || !haveMoney);
    edit_user_data(username, '-' + to_string(numInput), 2);
}

void deposit_cash(const string &username) {
    string msg;
    int numInput;
    do {
        if (!msg.empty())
            printf("The amount must be of bills 50, 100, 200\n");
        msg = "the amount you want to deposit";
        numInput = input_number(msg);
    } while (numInput % 50 != 0);
    edit_user_data(username, to_string(numInput), 2);
}

void transfer_balance(const string &username) {
    string otherUser, msg = "the amount you want to transfer";
    int numInput;
    bool haveMoney;
    do {
        printf("Enter the username you want to transfer the money to:");
        cin >> otherUser;
        if (username == otherUser)
            printf("You can not transfer money to the same account\n");
        numInput = input_number(msg);
        haveMoney = stoi(get_user_data(username, 2)) >= numInput;
        if (!haveMoney)
            printf("The amount you want to transfer is larger than what you have in your account\n");
    } while (username_index(otherUser) == -1 || username == otherUser || !haveMoney);
    edit_user_data(username, '-' + to_string(numInput), 2);
    edit_user_data(otherUser, to_string(numInput), 2);
}

void change_pin(const string &username) {
    string msg;
    int numInput;
    do {
        if (!msg.empty())
            printf("Make sure the PIN consists of only 4 digits");
        msg = "your new PIN";
        numInput = input_number(msg);
        msg = to_string(numInput);
        const auto msgLength = msg.length();
        if (msgLength < 4)
            for (char i = 0; i < 4 - msgLength; ++i)
                msg = '0' + msg;
    } while (msg.length() != 4);
    edit_user_data(username, msg, 1);
}
