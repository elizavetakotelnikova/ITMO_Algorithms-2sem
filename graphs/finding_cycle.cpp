#include <iostream>
#include <vector>

bool DFS(int V, std::vector<std::vector<int>> &adj_list, int u, int colours[], int prev) {
    colours[u] = 0;
    for (int j : adj_list[u]) {
        if ((colours[j] == 0) && (j != prev)) {
            return true;
        }
        if ((colours[j] == -1) && (DFS(V, adj_list, j, colours, u))) {
            return true;
        }
    }
    colours[u] = 1;
    return false;
}

void FindCycle(int V, std::vector<std::vector<int>> &adj_list) {
    int visited[V];
    for (int i = 0; i < V; i++) {
        visited[i] = -1;
    };
    for (int i = 0; i < V; i++) {
        if (visited[i] == -1) {
            if (DFS(V, adj_list, i, visited, -1)) {
                std::cout << "YES";
                return;
            };
        }
    }
    std::cout << "NO";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, u, v,i;
    std::vector<std::vector<int> > adj_list;
    std::cin >> N >> M;
    adj_list.resize(N);
    for (i = 0; i < M; i++) {
        std::cin >> u >> v;
        if (u != v) {
            adj_list[u - 1].push_back(v - 1);
            adj_list[v - 1].push_back(u - 1);
        }
    }
    FindCycle(N, adj_list);
}
