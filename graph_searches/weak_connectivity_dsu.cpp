#include <iostream>
#include <vector>
#include <set>
int get_root(int a, int dsu[]) {
    if (a == dsu[a]) {
        return a;
    }
    return dsu[a] = get_root(dsu[a], dsu);
}

void join (int a, int b, int dsu[], int rank[]) {
    a = get_root(a, dsu);
    b = get_root(b, dsu);
    if (a == b) {
        return;
    }
    if (rank[a] > rank[b]) {
        std::swap(a, b);
    }
    if (rank[a] == rank[b]) {
        rank[b]++;
    }
    dsu[a] = b;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, Q;
    int u, v;
    int i, j;
    int first, second;
    unsigned char s;
    std::cin >> N >> M >> Q;
    int dsu[N], rank[N];
    int size, requests_size, count_size;
    std::vector<std::pair<int, int>> requests;
    std::vector<std::pair<int, int>> deleted;
    std::set<std::pair<int, int>> edges;
    std::set<std::pair<int, int>>::iterator it;
    std::vector<unsigned char> count;
    std::vector<std::string> answers;
    int counter_answers = 0;
    std::pair<int, int> k;
    for (i = 0; i < N; i++) {
        dsu[i] = i;
        rank[i] = 0;
    }
    for (i = 0; i < M; i++) {
        std::cin >> u >> v;
        if (u < v) {
            k = std::make_pair(u - 1, v - 1);
        }
        else {
            k = std::make_pair(v - 1, u - 1);
        }
        edges.insert(k);
    }
    for (j = 0; j < Q; j++) {
        std::cin >> s;
        count.push_back(s);
        if (s == '?') {
            std::cin >> first >> second;
            k = std::make_pair(first - 1, second - 1);
            requests.push_back(k);
        } else {
            std::cin >> first >> second;
            if (first < second) {
                k = std::make_pair(first - 1, second - 1);
            }
            else {
                k = std::make_pair(second - 1, first - 1);
            }
            deleted.push_back(k);
            edges.erase(k);
        }
    }
    for(it = edges.begin(); it != edges.end(); it++) {
        k = *it;
        join(k.first, k.second, dsu, rank);
    }
    requests_size = requests.size() - 1;
    size = deleted.size() - 1;
    count_size = Q - 1;
    for (j = 0; j < Q; j++) {
        s = count[count_size - j];
        if (s == '?') {
            k = std::make_pair(first - 1, second - 1);
            k = requests[requests_size];
            requests_size--;
            first = k.first;
            second = k.second;
            if (first == second) {
                answers.push_back("YES");
            }
            else if (get_root(first, dsu) == get_root(second, dsu)) {
                answers.push_back("YES");
            }
            else {
                answers.push_back("NO");
            };
            requests.pop_back();
        } else {
            first = deleted[size].first;
            second = deleted[size].second;
            size--;
            join(first, second, dsu, rank);
        }
    }
    for (i = answers.size() - 1; i >= 0; i--) {
        std::cout << answers[i] << "\n";
    }
    return 0;
}
