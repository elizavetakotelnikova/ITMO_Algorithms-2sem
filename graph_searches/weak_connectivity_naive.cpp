#include <iostream>
#include <vector>
void DFS(int V, std::vector<std::vector<int>> &adj_list, int u, int colours[], int counter, int components[]) {
    colours[u] = 0;
    for (int j : adj_list[u]) {
        if (colours[j] == -1) {
            DFS(V, adj_list, j, colours, counter, components);
        }
    }
    components[u] = counter;
    colours[u] = 1;
}

void DetectComponents(int V, std::vector<std::vector<int>> &adj_list, int components[]) {
    int visited[V];
    int counter = 0;
    for (int i = 0; i < V; i++) {
        visited[i] = -1;
    };
    for (int i = 0; i < V; i++) {
        if (visited[i] == -1) {
            counter++;
            DFS(V, adj_list, i, visited, counter, components);
        }
    }
}

int main() {
    int N, M, u, v, i, j, Q, first, second;
    unsigned char s;
    std::string str;
    std::cin >> N >> M >> Q;
    int components[N];
    std::vector<std::vector<int>> adj_list;
    std::vector<int>::iterator it_one;
    std::vector<int>::iterator it_second;
    adj_list.resize(N);
    for (i = 0; i < M; i++) {
        std::cin >> u >> v;
        adj_list[u - 1].push_back(v - 1);
        adj_list[v - 1].push_back(u - 1);
    }
    DetectComponents(N, adj_list, components);
    for (j = 0; j < Q; j++) {
        std::cin >> s;
        if (s == '?') {
            std::cin >> first >> second;
            if (components[first - 1] == components[second - 1]) {
                std::cout << "YES" << "\n";
            } else {
                std::cout << "NO" << "\n";
            }
        } else {
            std::cin >> first >> second;
            it_one = std::find(adj_list[first - 1].begin(), adj_list[first - 1].end(), second - 1);
            adj_list[first - 1].erase(it_one);
            it_second = std::find(adj_list[second - 1].begin(), adj_list[second - 1].end(), first - 1);
            adj_list[second - 1].erase(it_second);
            DetectComponents(N, adj_list, components);
        }
    }
    return 0;
}
