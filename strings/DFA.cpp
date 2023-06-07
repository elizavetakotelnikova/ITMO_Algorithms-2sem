#include <iostream>
#include <string>
#include <regex>
int main() {
    std::string surname, name, middle_name, age;
    std::string number, city, street, d;
    const std::regex test(R"(^[A-Z][A-z]* [A-z][A-z]* [A-z][A-z]* [0-9][0-9]+ ([+]?[7]|[8])[(]?[0-9]{3}[)]?[-]?[0-9]{3}[-]?[0-9]{2}[-]?[0-9]{2} g.[A-Z][A-Z][A-Z], ul.[A-Z][A-z]*, d.[0-9][0-9]+$)");
    std::string N;
    bool flag = true;
    std::getline(std::cin, N);
    int k = stoi(N);
    for (int i = 0; i < k; i++) {
        flag = true;
        std::getline(std::cin, name);
        if (!std::regex_match(name, test)) {
            flag = false;
            }
        if (flag) {
            std::cout << "YES" << "\n";
        }
        else {
            std::cout << "NO" << "\n";
        }
        }
    return 0;
}
