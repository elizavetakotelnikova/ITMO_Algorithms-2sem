#include <iostream>
#include <string>
#include <vector>
#include <cmath>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int N, max;
    int number;
    std::vector<int> ans;
    std::vector<int> str;
    std::cin >> N >> max;
    for (int i = 0; i < N; i++) {
        std::cin >> number;
        if (number > max) {
            break;
        }
        str.push_back(number);
    };
    int size = str.size();
    ans.push_back(str.size());
    int i = 1;
    while (2*i - 1 < size) {
        bool flag = true;
        for (int j = 0; j < i; j++) {
            if (str[i - j - 1] != str[i + j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ans.push_back(size - i);
        }
        i++;
    }
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[ans.size() - i - 1] << " ";
    }
    return 0;
}
