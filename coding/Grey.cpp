#include <iostream>
#include <cmath>
int main() {
    int n, count_prev, j;
    std::cin >> n;
    int degree = pow(2, n);
    std::string codes[degree][n];
    codes[0][0] = '0';
    codes[1][0] = '1';
    int count_current = 2;
    for (int i = 1; i < n; i++) {
        count_prev = count_current;
        count_current *= 2;
        for (j = count_prev - 1; j >= 0; j--) {
            codes[j][i] += '0';
            codes[count_current - j - 1][i] += '1';
            codes[j][i] += codes[j][i-1];
            codes[count_current - j - 1][i] += codes[j][i-1];
        }
    }

    for (int i = 0; i < degree; i++) {
        std::cout << codes[i][n-1] << "\n";
    }
    return 0;
}
