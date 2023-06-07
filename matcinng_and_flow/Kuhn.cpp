#include <vector>
#include <cstring>
#include <set>
#include <iostream>

bool DFS(int v, int visited[], int N, int matching[], std::vector <std::vector <int>> &adj_list) {
    if (visited[v])
        return false;
    visited[v] = true;
    for (int j: adj_list[v]) {
        if (matching[j] == -1 or DFS(matching[j], visited, N, matching, adj_list)) {
            matching[j] = v;
            return true;
        }
    }
    return false;
}

void FindPares(int V, std::vector <std::vector <int>> &adj_list, int is_safe[]) {
    int matching[V];
    int visited[V];
    int counter = 0;
    for (int i = 0; i < V; i++) {
        matching[i] = -1;
    }
    for (int i = 0; i < V; i++) {
        if (is_safe[i] == -1) {
            continue;
        }
        for (int j = 0; j < V; j++) {
            visited[j] = false;
        }
        DFS(i, visited, V, matching, adj_list);
    }
    for (int i = 0; i < V; i++) {
        if (matching[i] != -1) {
            //std::cout << i << " ";
            counter++;
        }
    }
    std::cout << counter;
}

int main() {
    int N, M, Q;
    int u, v, i, j;
    std::cin >> N >> M;
    if (N == 0 or M == 0) {
        std::cout << "0";
        return 0;
    }
    int matrix[N][M];
    std::vector<std::vector<int>> adj_list;
    std::set<std::pair<int, int>> wrong;
    std::cin >> Q;
    int it = 0;
    for (i = 0; i < Q; i++) {
        std::cin >> u >> v;
        wrong.insert({u - 1, v - 1});
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (wrong.find({i, j}) == wrong.end()) {
                matrix[i][j] = it;
            }
            else {
                //std::cout << it;
                matrix[i][j] = -1;
                wrong.erase({i, j});
            }
            it++;
        }
    };
    adj_list.resize(it);
    int is_safe[it];
    v = it;
    it = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (matrix[i][j] >= 0) {
                is_safe[it] = 1;
                if ((j < (M - 1)) && matrix[i][j + 1] >= 0) {
                    adj_list[it].push_back(it + 1);
                    adj_list[it + 1].push_back(it);
                }
                if ((j > 0) && matrix[i][j - 1] >= 0) {
                    adj_list[it].push_back(it - 1);
                    adj_list[it - 1].push_back(it);
                }
                if ((i < (N - 1)) && matrix[i + 1][j] >= 0) {
                    adj_list[it].push_back(matrix[i+1][j]);
                    adj_list[matrix[i + 1][j]].push_back(it);
                }
                if ((i > 0) && matrix[i - 1][j] >= 0) {
                    adj_list[it].push_back(matrix[i-1][j]);
                    adj_list[matrix[i - 1][j]].push_back(it);
                }
            }
            else {
                is_safe[it] = -1;
            }
            it++;
        }
    }
    FindPares(it, adj_list, is_safe);
    return 0;
}
