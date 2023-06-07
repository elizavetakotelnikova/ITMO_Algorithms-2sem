#include <iostream>
#include <vector>
void DFS(int V, std::vector<std::vector<int>> &adj_list, int u, int colours[]) {
    colours[u] = 0;
    for (int j : adj_list[u]) {
        if (colours[j] == -1) {
            DFS(V, adj_list, j, colours);
        }
    }
    colours[u] = 1;
}

int DetectComponents(int V, std::vector<std::vector<int>> &adj_list) {
    int visited[V];
    int counter = 0;
    for (int i = 0; i < V; i++) {
        visited[i] = -1;
    };
    for (int i = 0; i < V; i++) {
        if (visited[i] == -1) {
            counter++;
            DFS(V, adj_list, i, visited);
        }
    }
    return counter;
}

int main() {
    int N, M, u, v, i, j;
    std::string str;
    std::cin >> N >> M;
    int matrix[N][M];
    std::vector<std::vector<int>> adj_list;
    int it = 0;
    for (i = 0; i < N; i++) {
        std::cin >> str;
        for (j = 0; j < M; j++) {
            if (str[j] == '.') {
                matrix[i][j] = it;
                it++;
            }
            else {
                matrix[i][j] = -1;
            }
        }
    };
    adj_list.resize(it);
    v = it;
   it = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (matrix[i][j] >= 0) {
                if (matrix[i][j + 1] >= 0) {
                    adj_list[it].push_back(it + 1);
                    adj_list[it + 1].push_back(it);
                }
                if (matrix[i][j - 1] >= 0) {
                    adj_list[it].push_back(it - 1);
                    adj_list[it - 1].push_back(it);
                }
                if (matrix[i + 1][j] >= 0) {
                    adj_list[it].push_back(matrix[i+1][j]);
                    adj_list[matrix[i + 1][j]].push_back(it);
                }
                if (matrix[i - 1][j] >= 0) {
                    adj_list[it].push_back(matrix[i-1][j]);
                    adj_list[matrix[i - 1][j]].push_back(it);
                }
                it++;
            }
        }
    }
    int k = DetectComponents(v, adj_list);
    std::cout << k;
    return 0;
}
