#include <iostream>
#include <vector>
#include <set>

long long get_root(long long a, long long dsu[]) {
    if (a == dsu[a]) {
        return a;
    }
    return dsu[a] = get_root(dsu[a], dsu);
}

void join (long long a, long long b, long long dsu[], long long rank[]) {
    a = get_root(a, dsu);
    b = get_root(b, dsu);
    if (a == b) {
        return;
    }
    if (rank[a] > rank[b]) {
        dsu[b] = a;
        rank[a]++;
    }
    else {
        dsu[a] = b;
        rank[b]++;
    }
}

long long Kruskala(std::set<std::pair<long long, std::pair<long long, long long>>> &edges, long long N, long long M) {
    long long counter = 0, sum_weight = 0;
    long long start, end, i;
    long long dsu[N], rank[N];
    for (i = 0; i < N; i++) {
        dsu[i] = i;
        rank[i] = 0;
    }
    std::set<std::pair<long long, std::pair<long long, long long>>>::iterator it;
    for (it = edges.begin(); it != edges.end(); it++) {
        std::pair<long long, std::pair<long long, long long>> cur_ed = *it;
        start = cur_ed.second.first;
        end = cur_ed.second.second;
        if ((get_root(start, dsu)) != get_root(end, dsu)) {
            join(start, end, dsu, rank);
            counter++;
            sum_weight += cur_ed.first;
        }
        if (counter == (N - 1)) {
            return sum_weight;
        }
    }
    return sum_weight;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::set<std::pair<long long, std::pair<long long, long long>>> edges;
    long long N, M;
    long long u, v, weight, i;
    std::cin >> N >> M;
    for (i = 0; i < M; i++) {
        std::cin >> u >> v >> weight;
        edges.insert({weight, {u - 1, v - 1}});
    }
    std::cout << Kruskala(edges, N, M);
    return 0;
}
