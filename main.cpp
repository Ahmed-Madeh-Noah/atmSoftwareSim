#include <iostream>
#include <string>

using namespace std;

const string users[2][2] = {{"Ahmed", "0123"},
                            {"Noah",  "9876"}};

string login();

int main() {
    const string userId = login();
    return 0;
}

string login() {
    string userId;
    printf("Enter your username:");
//    cin >> userId;
//    short int trials = 0;
//    while
//    for (const auto user: users)
//        if (user[0] == userId)
//            return userId;
    return "";
}