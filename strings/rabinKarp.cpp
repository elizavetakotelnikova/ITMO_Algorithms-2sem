#include <iostream>
#include <string>
#include <vector>
#include <cmath>
int const_values[5] = {3651311, 3455119, 22414, 1953523, 271545};
int const_values_two[3] = {113451, 3112411, 734184};

unsigned long long H(std::string x, unsigned long long size) {
    int i = 0;
    unsigned long long res = 0;
    while (i != x.length()) {
        res += (int)x[i];
        i++;
    }
    return res % size;
}

unsigned long long H1(unsigned char x, unsigned long long size) {
    unsigned char cur = (int)(x - 'a' + 1);
    return cur % size;
}

int main() {
    std::string first, second, str;
    std::cin >> first;
    std::cin >> second;
    int n = first.length();
    int m = second.length();
    std::vector<int> positions;
    int counter = 0;
    //BuildHash(first, second);
    for (int i = 0; i < m; i++) {
        str += first[i];
    }
    unsigned long long HashFirst = H(str, 999991);
    unsigned long long HashSecond = H(second, 999991);
    for (int i = 0; i < (n - m) + 1; i++) {
        if (HashFirst == HashSecond) {
            bool flag = true;
            for (int j = 0; j < m; j++) {
                if (first[i + j] != second[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                positions.push_back(i);
                counter++;
            }
        }
        HashFirst =  HashFirst - (int)first[i] + (int)first[i + m];
        HashFirst %= 999991;
    }
    std::cout << counter << "\n";
    for (int i = 0; i < positions.size(); i++) {
        std::cout << positions[i] << " ";

    }
    return 0;
}
