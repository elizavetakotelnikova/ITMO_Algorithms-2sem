#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    std::string first, second, str;
    std::cin >> first;
    std::cin >> second;
    int n = first.length();
    int m = second.length();
    std::vector<int> positions;
    int counter = 0;
    for (int i = 0; i < (n - m) + 1; i++) {
        str = first.substr(i, m);
        if (str == second) {
            positions.push_back(i);
            counter++;
        }
    }
    std::cout << counter << "\n";
    for (int i = 0; i < positions.size(); i++) {
        std::cout << positions[i] << " ";

    }
    return 0;
}
