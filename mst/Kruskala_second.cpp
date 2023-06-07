#include <iostream>
#include <vector>
#include <set>
#include <limits>
int inf = std::numeric_limits<double>::infinity();

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
        dsu[b] = a;
        rank[a]++;
    }
    else {
        dsu[a] = b;
        rank[b]++;
    }
}

void Kruskala(std::set<std::pair<int, std::pair<int, int>>> &edges, int N, int M) {
    int counter = 0, sum_weight = 0;
    int start, end, i;
    int dsu[N], rank[N];
    std::vector<std::pair<int, int>> mst_edges;
    for (i = 0; i < N; i++) {
        dsu[i] = i;
        rank[i] = 0;
    }
    int max_cost = 0;
    std::set<std::pair<int, std::pair<int, int>>>::iterator it;
    std::pair<int, std::pair<int, int>> cur_ed;
    for (it = edges.begin(); it != edges.end(); it++) {
        cur_ed = *it;
        start = cur_ed.second.first;
        end = cur_ed.second.second;
        if ((get_root(start, dsu)) != get_root(end, dsu)) {
            mst_edges.emplace_back(start, end);
            join(start, end, dsu, rank);
            counter++;
            sum_weight += cur_ed.first;
        }
        if (counter == (N - 1)) {
            std::cout << sum_weight << " ";
            break;
        }
    }
    int mst2_weight = inf;
    for (int k = 0; k < (N - 1); k++) {
        sum_weight = 0;
        counter = 0;
        for (i = 0; i < N; i++) {
            dsu[i] = i;
            rank[i] = 0;
        }
        int start_mst = mst_edges[k].first;
        int end_mst = mst_edges[k].second;
        for (it = edges.begin(); it != edges.end(); it++) {
            cur_ed = *it;
            start = cur_ed.second.first;
            end = cur_ed.second.second;
            if (start == start_mst && end == end_mst) {
                continue;
            }
            if ((get_root(start, dsu)) != get_root(end, dsu)) {
                join(start, end, dsu, rank);
                sum_weight += cur_ed.first;
                counter++;
            }
            if (counter == (N - 1)) {
                continue;
            }
        }
        mst2_weight = std::min(mst2_weight, sum_weight);
    }
    std::cout << mst2_weight << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::set<std::pair<int, std::pair<int, int>>> edges;
    int N, M;
    int u, v, weight, i;
    std::cin >> N >> M;
    for (i = 0; i < M; i++) {
        std::cin >> u >> v >> weight;
        edges.insert({weight, {u - 1, v - 1}});
    }
    Kruskala(edges, N, M);
    return 0;
}
