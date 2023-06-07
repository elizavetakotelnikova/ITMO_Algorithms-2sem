#include <iostream>
#include <vector>
#include <limits>
int inf = std::numeric_limits<double>::infinity();

void floyd(int V, std::vector<std::vector<int>> &d) {
    for (int i = 0; i < V; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if ((d[u][i] != inf) and (d[i][v] != inf)) {
                    d[u][v] = std::min(d[u][v], d[u][i] + d[i][v]);
                }
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, K, u, v, i, first, second, weight, answer;
    std::cin >> N >> M;
    std::vector <std::vector <int>> adj_list(N, std::vector <int>(N, inf));
    for (i = 0; i < N; i++) {
        adj_list[i][i] = 0;
    }
    for (i = 0; i < M; i++) {
        std::cin >> u >> v >> weight;
        adj_list[u - 1][v - 1] = weight;
        adj_list[v - 1][u - 1] = weight;
    }
    floyd(N, adj_list);
    answer = 0;
    for (i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (adj_list[i][j] > answer and adj_list[i][j] != inf) {
                answer = adj_list[i][j];
            }
        }
    }
    std::cout << answer;
    return 0;
}
