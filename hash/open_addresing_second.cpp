#include <iostream>
#include <cmath>
#include <vector>

int H(int x, int size) {
    return x % 99999991 % size;
}

void insert(std::vector<std::pair<float, int>> &hash_table, int size, int &counter, int ans, int res_ans) {
    int h = H(ans, size);
    while (hash_table[h].first != 0.5) {
        if (hash_table[h].first == res_ans) {
            break;
        }
        h += 4;
    }
    hash_table[h].first = res_ans;
    counter += hash_table[h].second;
    hash_table[h].second++;
}

int main() {
    int N, current, S;
    float ans;
    std::cin >> N;
    S = 1000000;
    std::vector<std::pair<float, int>> hash_table;
    hash_table.resize(2*S + 2);
    int counter = 0;
    for (int i = 0; i < 2*S + 2; i++) {
        hash_table[i].first = 0.5;
        hash_table[i].second = 0;
    }
    for (int i = 0; i < N; i++) {
        std::cin >> current;
        ans = current - i;
        int res_ans = ans;
        if (ans < 0) {
            ans = std::abs(ans) + S;
        }
        insert(hash_table, 2*S + 2, counter, ans, res_ans);
    }
    std::cout << counter;
    return 0;
}
