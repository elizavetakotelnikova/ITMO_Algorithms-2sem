#include <iostream>
#include <vector>
#include <limits>
int inf = std::numeric_limits<double>::infinity();

int dfs(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &flow, int u, int cmin, int visited[], int end, int N) {
    if (u == end) {
        return cmin;
    }
    visited[u] = 1;
    for (int i = 0; i < N; i++) {
            if ((visited[i] == -1) and (flow[u][i] < graph[u][i])) {
                int diff = dfs(graph, flow, i, std::min(cmin, (graph[u][i] - flow[u][i])), visited, end, N);
                if (diff > 0) {
                    flow[u][i] += diff;
                    flow[i][u] -= diff;
                    return diff;
                }
            }
    }
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M;
    int u, v, c, maxc = 0;
    std::cin >> N >> M;
    std::vector <std::vector <int>> graph(N, std::vector <int>(N, 0));
    std::vector <std::vector <int>> flow(N, std::vector <int>(N, 0));
    std::vector<std::vector<int>> adj_list;
    adj_list.resize(N);
    for (int i = 0; i < M; i++) {
        std::cin >> u >> v >> c;
        graph[u - 1][v - 1] = c;
    }
    int visited[N];
    for (int i = 0; i < N; i++) {
        visited[i] = -1;
    }
    while (int cur = dfs(graph, flow, 0, inf, visited, N - 1, N)) {
        maxc += cur;
        for (int i = 0; i < N; i++) {
            visited[i] = -1;
        }
    }
    std::cout << maxc;
    return 0;
}
