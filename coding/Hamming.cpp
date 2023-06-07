#include <iostream>
#include <cmath>
int CheckDegree(int len) {
    int counter = 0;
    while (len >= 1) {
        len /= 2;
        counter++;
    };
    return counter;
};

int CheckBites(std::string message) {
    int i, error = 0;
    for (i = 0; i < message.length(); i++)
        if (message[i] == '1') {
            error ^= i + 1;
        }
    return error;
}

void Decode(std::string message) {
    int error, counter;
    error = 0;
    int deg = CheckDegree(message.length());
    error = CheckBites(message);
    if (error) {
        message[error - 1]^='0' ^ '1';
    };
    counter = 1;
    for (int i = 0; i < deg; i++) {
        message.erase(counter - 1 - i, 1);
        counter = counter*2;
    };
    std::cout << message << "\n";
};

int main() {
    int n;
    std::string str;
    std::cin >> n;
    while (std::cin >> str) {
        Decode(str);
    }
    return 0;
}
