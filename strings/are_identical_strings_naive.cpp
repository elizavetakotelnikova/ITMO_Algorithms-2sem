#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int N, M, start, end, length;
    std::cin >> N >> M;
    std::string first, second, str1, str2;
    std::cin >> first;
    std::vector<int> positions;
    int counter = 0;
    for (int i = 0; i < M; i++) {
        std::cin >> start >> end >> length;
        str1 = first.substr(start - 1, length);
        str2 = first.substr(end - 1, length);
        if (str1 == str2) {
            counter++;
        }
    }
    std::cout << counter << "\n";
    return 0;
}
