#include <iostream>
#include <string>

using namespace std;

const string users[2][2] = {{"Ahmed", "0123"},
                            {"Noah",  "9876"}};

string login();

bool confirm_user_data(const string &userData, short int index);

int main() {
    const string username = login();
    cout << "\nUsername = " << username << '\n';
    return 0;
}

string login() {
    string username, password;
    char counter = 0;
    bool user_present_flag;
    do {
        printf("You have %d trial/s to\nEnter your username:", 3 - counter);
        cin >> username;
        ++counter;
        user_present_flag = confirm_user_data(username, 0);
    } while (!user_present_flag && counter < 3);
    if (user_present_flag) {
        counter = 0;
        do {
            printf("You have %d trial/s to\nEnter your password:", 3 - counter);
            cin >> password;
            ++counter;
            if (confirm_user_data(password, 1))
                return username;
        } while (counter < 3);
    }
    return "";
}

bool confirm_user_data(const string &userData, const short int index) {
    for (auto user: users)
        if (user[index] == userData)
            return true;
    return false;
}