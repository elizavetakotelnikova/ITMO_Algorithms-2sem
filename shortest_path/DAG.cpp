#include <iostream>
#include <vector>
#include <vector>
#include <limits>
int inf = std::numeric_limits<double>::infinity();
struct Node {
    int data ;
    Node *next;
    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

struct Stack {
    Node *head = nullptr;
};

void Push(Stack *S, int value) {
    Node *new_node = new Node(value);
    new_node->data = value;
    new_node->next = S->head;
    S->head = new_node;
}

int Pop(Stack *S) {
    struct Node *deleted = S->head;
    int data = deleted->data;
    S->head = deleted->next;
    free(deleted);
    return data;
}
bool Is_empty(Stack *S) {
    if (S->head == nullptr) {
        return true;
    }
    return false;
}

void DFS(int V, std::vector<std::vector<int>> &adj_matrix, int u, int colours[], struct Stack &TopSort) {
    colours[u] = 0;
    for (int j = 0; j < V; j++) {
        if (adj_matrix[u][j] != inf) {
            if (colours[j] == -1) {
                DFS(V, adj_matrix, j, colours, TopSort);
            }
        }
    }
    colours[u] = 1;
    Push(&TopSort, u);
}

void DAG(int V, std::vector<std::vector<int>> &adj_matrix, int distance[]) {
    int visited[V];
    int cur_u;
    struct Stack TopSort;
    for (int i = 0; i < V; i++) {
        visited[i] = -1;
    };
    for (int i = 0; i < V; i++) {
        if (visited[i] == -1) {
            DFS(V, adj_matrix, i, visited, TopSort);
        }
    }
    while (!Is_empty(&TopSort)) {
        cur_u = Pop(&TopSort);
        for (int j = 0; j < V; j++) {
            if (distance[cur_u] != inf and (adj_matrix[cur_u][j] != inf)) {
                distance[j] = std::min(distance[j], distance[cur_u] + adj_matrix[cur_u][j]);
            }
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, u, v, i, j, start, end, weight;
    std::cin >> N >> M;
    std::vector <std::vector <int>> adj_matrix(N, std::vector <int>(N, inf));
    std::cin >> start >> end;
    int distance[N];
    for (i = 0; i < M; i++) {
        std::cin >> u >> v >> weight;
        adj_matrix[u - 1][v - 1] = weight;
    }
    for (j = 0; j < N; j++) {
        distance[j] = inf;
    }
    distance[start - 1] = 0;
    DAG(N, adj_matrix, distance);
    if (distance[end - 1] == inf) {
        std::cout << -1;
        return 0;
    }
    std::cout << distance[end - 1];
    return 0;
}
