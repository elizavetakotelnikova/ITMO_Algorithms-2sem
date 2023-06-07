#include <iostream>
#include <cmath>

int H(int x, int size) {
    return x % 9999991 % (size + 1) ;
}

void insert(int x, bool hash_table[], int size) {
    hash_table[H(x, size)] = true;
}

bool contains(int x, const bool hash_table[], int size) {
    if (!hash_table[H(x, size)]) {
        return false;
    }
    return true;
}

int main() {
    int N, current;
    std::cin >> N;
    bool hash_table[N + 1];
    for (int i = 0; i < N; i++) {
        hash_table[i] = false;
    }
    for (int i = 0; i < N; i++) {
        std::cin >> current;
        insert(current, hash_table, N);
    }

    for (int i = 0; i < N; i++) {
        std::cin >> current;
        if (!contains(current, hash_table, N)) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}
