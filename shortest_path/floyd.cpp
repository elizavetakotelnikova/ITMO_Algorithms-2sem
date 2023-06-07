#include <iostream>
#include <vector>
#include <limits>
int inf = std::numeric_limits<double>::infinity();

void floyd(int V, int K, std::vector<std::vector<int>> &d) {
    for (int i = 0; i < V; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (((abs(u - i)) <= K) and (abs(v - i) <= K)) {
                    if ((d[u][i] != inf) and (d[i][v] != inf)) {
                        d[u][v] = std::min(d[u][v], d[u][i] + d[i][v]);
                    }
                }
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, K, u, v, i, Q, first, second, weight;
    std::cin >> N >> M >> K;
    std::vector <std::vector <int>> adj_list(N, std::vector <int>(N, inf));
    for (i = 0; i < M; i++) {
        std::cin >> u >> v >> weight;
        adj_list[u - 1][v - 1] = weight;
    }
    for (i = 0; i < N; i++) {
        adj_list[i][i] = 0;
    }
    std::cin >> Q;
    floyd(N, K, adj_list);
    for (int j = 0; j < Q; j++) {
        std::cin >> u >> v;
        if (u == v) {
            std::cout << 0;
        }
        else if (adj_list[u - 1][v - 1] != inf) {
            std::cout << adj_list[u - 1][v - 1] << "\n";
        } else {
            std::cout << -1 << "\n";
        }
    }
}
