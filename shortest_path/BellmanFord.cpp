#include <iostream>
#include <vector>
#include <limits>
int inf = std::numeric_limits<double>::infinity();

void BellmanFord(int V, int E, int edges_list[][3], int distance[]) {
    int u, v, weight, j, i;
    bool flag;
    for (j = 0; j < (V - 1); j++) {
        flag = false;
        for (i = 0; i < 2*E; i++) {
            u = edges_list[i][0];
            v = edges_list[i][1];
            weight = edges_list[i][2];
            if ((distance[u] != inf)) {
                if (distance[v] > distance[u] + weight) {
                    flag = true;
                    distance[v] = distance[u] + weight;
                }
            }
        }
        if (!flag) {
            return;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int V, M, u, v, i,  weight, start, N, j, Q, answer, end;
    std::cin >> V >> M >> Q >> start;
    int edges_list[2*M][3];
    for (i = 0; i < M; i++) {
        std::cin >> u >> v >> weight;
        edges_list[i][0] = u - 1;
        edges_list[i][1] = v - 1;
        edges_list[i][2] = weight;
        edges_list[i + M][0] = v - 1;
        edges_list[i + M][1] = u - 1;
        edges_list[i + M][2] = weight;
    }
    int pred[V];
    int distance[V];
    for (i = 0; i < V; i++) {
        pred[i] = inf;
        distance[i] = inf;
    }
    distance[start - 1] = 0;
    BellmanFord(V, M, edges_list, distance);
    for (i = 0; i < Q; i++) {
        std::cin >> end;
        answer = distance[end - 1];
        if (answer == inf) {
            std::cout << -1 << "\n";
        }
        else {
            std::cout << answer << "\n";
        }
    }
    return 0;
}
