#include <iostream>
#include <cmath>
#include <string>
#include <vector>
int value;
int const_values[5] = {3651311, 3455119, 22414, 1953523, 271545};
int const_values_two[3] = {113451, 3112411, 734184};

unsigned long long H1(std::string x, unsigned long long size) {
    int i = 0;
    unsigned long long res = 0;
    while (i != x.length()) {
        int cur = (int)(x[i] - 'a' + 1);
        res += cur * const_values_two[i % 3]+ cur* const_values[(i + 2) % 5] - cur;
        i++;
    }
    return res % 999999991 % size;
}

unsigned long long H2(std::string x, unsigned long long size) {
    int i = 0;
    long long res = 0;
    while (i != x.length()) {
        int cur = (int)(x[i] - 'a' + 1);
        res += cur * const_values[i % 5]*value + cur*const_values_two[i % 3];
        i++;
    }
    return res % 9999999991 % size;
}

void insert_again(std::vector<std::string> &hash_table, unsigned long long size, const std::string& str) {
    unsigned long long h = H1(str, size);
    unsigned long long h1;
    std::string x, y;
    x = str;
    while (!(std::empty(hash_table[h]))) {
        y = x;
        x = hash_table[h];
        hash_table[h] = y;
        h = H2(x, size);
    }
    hash_table[h] = x;
}

void insert(std::vector<std::string> &hash_table, unsigned long long size, const std::string& str) {
    unsigned long long h = H1(str, size);
    unsigned long long h1;
    std::string x, y;
    x = str;
    unsigned long long cur_hash = h;
    while (!(std::empty(hash_table[h]))) {
        y = x;
        x = hash_table[h];
        hash_table[h] = y;
        h = H2(x, size);
        if (h == H1(str, size)) {
            value *= 11;
            std::vector<std::string> new_hash;
            for (int i = 0; i < size; i++) {
                if (!(std::empty(hash_table[i]))) {
                    new_hash.push_back(hash_table[i]);
                }
            }
            size *= 2;
            hash_table.resize(size);
            for (int i = 0; i < size; i++) {
                hash_table[i] = "";
            }
            for (int i = 0; i < new_hash.size(); i++) {
                insert_again(hash_table, size, new_hash[i]);
            }
            insert_again(hash_table, size, x);
            return;
        }
    }
    hash_table[h] = x;
}

bool contains(std::vector<std::string> &hash_table, unsigned long long size, const std::string& str) {
    unsigned long long h = H1(str, size);
    unsigned long long h2;
    if (hash_table[h] == str) {
        return true;
    }
    h2 = H2(str, size);
    if (hash_table[h2] == str) {
        return true;
    }
    return false;
}

int main() {
    int current;
    long long N, S;
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    std::string str;
    std::cin >> N;
    S = N;
    std::vector<std::string> hash_table;
    std::vector<std::string> first;
    std::vector<std::string> second;
    S = N*5;
    int value = 3627811;
    hash_table.resize(S);
    std::vector<std::string> second_hash_table;
    second_hash_table.resize(S);
    std::vector<std::string> third_hash_table;
    std::vector<std::string>::iterator it;
    third_hash_table.resize(S);
    int counter_first = 0;
    int counter_second = 0;
    int counter_third = 0;
    for (int i = 0; i < S; i++) {
        hash_table[i] = "";
        second_hash_table[i] = "";
        third_hash_table[i] = "";
    }
    for (int i = 0; i < N; i++) {
        std::cin >> str;
        first.push_back(str);
        if (!contains(hash_table, hash_table.size(), str)) {
            insert(hash_table, hash_table.size(), str);
        }
    }
    for (int i = 0; i < N; i++) {
        std::cin >> str;
        second.push_back(str);
        if (!contains(second_hash_table, second_hash_table.size(), str)) {
            insert(second_hash_table, second_hash_table.size(), str);
        }
    }
    for (int i = 0; i < N; i++) {
        std::cin >> str;
        if (!contains(third_hash_table, third_hash_table.size(), str)) {
            insert(third_hash_table, third_hash_table.size(), str);
        }
        if (contains(hash_table, hash_table.size(), str)) {
            if (contains(second_hash_table, second_hash_table.size(), str)) {
                continue;
            }
            else {
                counter_third++;
                counter_first++;
            }
        }
        else if (contains(second_hash_table, second_hash_table.size(), str)) {
            counter_third++;
            counter_second++;
        }
        else {
            counter_third += 3;
        }
    }
    it = first.begin();
    while (it != first.end()) {
        str = *it;
        if (contains(second_hash_table, second_hash_table.size(), str))
        {
            if (contains(third_hash_table, third_hash_table.size(), str)) {
                it++;
                continue;
            }
            else {
                counter_first++;
                counter_second++;
            }
        }
        else if (contains(third_hash_table, third_hash_table.size(), str)) {
            it++;
            continue;
        }
        else {
            counter_first += 3;
        }
        it++;
    }
    it = second.begin();
    while (it != second.end()) {
        str = *it;
        if (contains(hash_table, hash_table.size(), str)) {
            it++;
            continue;
        }
        else if (contains(third_hash_table, third_hash_table.size(), str)) {
            it++;
            continue;
        }
        else {
            counter_second += 3;
        }
        it++;
    }
    std::cout << counter_first << " " << counter_second << " " << counter_third;
    return 0;
}
