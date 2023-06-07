#include <iostream>
#include <vector>
void DFS(int V, std::vector<std::vector<int>> &adj_list, int u, int colours[], int counter, int components[], int safe[], std::vector<int> &is_safe) {
    colours[u] = 0;
    if (safe[u] == 1) {
        is_safe[counter - 1] = 1;
    }
    for (int j : adj_list[u]) {
        if (colours[j] == -1) {
            if (safe[j] == 1) {
                is_safe[counter - 1] = 1;
            }
            DFS(V, adj_list, j, colours, counter, components, safe, is_safe);
        }
    }
    components[u] = counter;
    colours[u] = 1;
}

int DetectComponents(int V, std::vector<std::vector<int>> &adj_list, int components[], int safe[], std::vector<int> &is_safe) {
    int visited[V];
    int counter = 0;
    for (int i = 0; i < V; i++) {
        visited[i] = -1;
    };
    for (int i = 0; i < V; i++) {
        if (visited[i] == -1) {
            counter++;
            is_safe.push_back(0);
            DFS(V, adj_list, i, visited, counter, components, safe, is_safe);
        }
    }
    return counter;
}

int main() {
    int N, M, u, v, i, j;
    std::string str;
    std::cin >> N >> M;
    int safe[N];
    std::vector<int> is_safe;
    int components[N];
    std::vector<std::vector<int>> adj_list;
    adj_list.resize(N);
    for (i = 0; i < M; i++) {
        std::cin >> u >> v;
        adj_list[u - 1].push_back(v - 1);
        adj_list[v - 1].push_back(u - 1);
    }
    for (int i = 0; i < N; i++) {
        std::cin >> safe[i];
    }
    int k = DetectComponents(N, adj_list, components, safe, is_safe);
    std::cout << k << "\n";
    for (int i = 0; i < N; i++) {
        std::cout << components[i] << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < k; i++) {
        std::cout << is_safe[i] << " ";
    }
    return 0;
}
