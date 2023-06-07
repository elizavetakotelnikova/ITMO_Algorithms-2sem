#include <iostream>
#include <string>
#include <vector>
#include <cmath>
int main() {
    std::string str;
    std::cin >> str;
    int n = str.length();
    int a[n];
    a[0] = 0;
    std::cout << 0 << " ";
    for (int i = 1; i < n; i++) {
        int j = a[i - 1];
        while (j > 0 && str[i] != str[j]) {
            j = a[j - 1];
        }
        if (str[i] == str[j]) {
            j++;
        }
        a[i] = j;
        std::cout << j << " ";
    }
    return 0;
}
