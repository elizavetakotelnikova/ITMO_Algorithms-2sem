#include <iostream>
#include <cmath>
#include <vector>

int H(int x, int size) {
    return x % 99999991 % size;
}

void insert(std::vector<std::pair<std::pair<int, int>, bool>> &hash_table, int size, int x) {
    int h = H(x, size);
    while (hash_table[h].first.first != -1 or hash_table[h].second) {
        if (hash_table[h].first.first == x) {
            break;
        }
        h = (h + 1000) % size;
    }
    hash_table[h].first.first = x;
    hash_table[h].first.second++;
    hash_table[h].second = false;
}

void deleteElement(std::vector<std::pair<std::pair<int, int>, bool>> &hash_table, int size, int x) {
    int h = H(x, size);
    while (hash_table[h].first.first != x) {
        if (hash_table[h].first.first == -1 && !hash_table[h].second) {
            return;
        }
        h = (h + 1000) % size;
    }
    hash_table[h].second = true;
    hash_table[h].first = {-1, 0};
}

int returnValue(std::vector<std::pair<std::pair<int, int>, bool>> &hash_table, int size, int x) {
    int h = H(x, size);
    while (hash_table[h].first.first != -1 or hash_table[h].second) {
        if (hash_table[h].first.first == x) {
            return hash_table[h].first.second;
        }
        h = (h + 1000) % size;
    }
    return -1;
}

void setValue(std::vector<std::pair<std::pair<int, int>, bool>> &hash_table, int size, int x) {
    int h = H(x, size);
    while (hash_table[h].first.first != -1 or hash_table[h].second) {
        if (hash_table[h].first.first == x) {
            break;
        }
        h = (h + 1000) % size;
    }
    hash_table[h].first.first = x;
    hash_table[h].first.second--;
    hash_table[h].second = false;
}

bool contains(std::vector<std::pair<std::pair<int, int>, bool>> &hash_table, int size, int x) {
    int h = H(x, size);
    while (hash_table[h].first.first != -1 or hash_table[h].second) {
        if (hash_table[h].first.first == x) {
            return true;
        }
        h = (h + 1000) % size;
    }
    return false;
}

int main() {
    int N, x, y, S;
    float ans;
    std::cin >> N;
    S = N*5;
    std::vector<std::pair<std::pair<int, int>, bool>> hash_table;
    std::vector<std::pair<std::pair<int, int>, bool>> hash_table_y;
    std::vector<std::pair<float, int>> requests;
    std::pair<int, int> current;
    hash_table.resize(2*S + 2);
    hash_table_y.resize(2*S + 2);
    int counter = 0;
    for (int i = 0; i < 2*S + 2; i++) {
        hash_table[i].first = {-1, 0};
        hash_table[i].second = false;
        hash_table_y[i].first = {-1, 0};
        hash_table_y[i].second = false;
    }
    for (int i = 0; i < N; i++) {
        std::cin >> x >> y;
        if (!contains(hash_table, 2*S + 2, x) && !contains(hash_table_y, 2*S + 2, y)) {
            insert(hash_table, 2*S + 2, x);
            insert(hash_table_y, 2*S + 2, y);
            requests.emplace_back(x, y);
        }
    }
    for (int i = 0; i < requests.size(); i++) {
        x = requests[i].first;
        y = requests[i].second;
        if (returnValue(hash_table, 2*S + 2, x) > 1) {
            counter++;
            deleteElement(hash_table, 2*S + 2, x);
            setValue(hash_table_y, 2*S + 2, y);
        }
        else if (returnValue(hash_table_y, 2*S + 2, y) > 1) {
            counter++;
            deleteElement(hash_table_y, 2*S + 2, y);
            setValue(hash_table, 2*S + 2, x);
        }
        if (returnValue(hash_table, 2*S + 2, x) == 1 && returnValue(hash_table_y, 2*S + 2, y) == 1) {
            counter++;
            deleteElement(hash_table, 2*S + 2, x);
            deleteElement(hash_table_y, 2*S + 2, y);
        }
        if (counter > 3) {
            break;
        }
    }
    if (counter == 3) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
    return 0;
}
