#include <iostream>
#include <vector>
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

void DFS(int V, std::vector<std::vector<int>> &adj_list, int u, int colours[], struct Stack &TopSort) {
    colours[u] = 0;
    for (int j : adj_list[u]) {
        if (colours[j] == -1) {
            DFS(V, adj_list, j, colours, TopSort);
        }
    }
    colours[u] = 1;
    Push(&TopSort, u);
}

void FindPath(int V, std::vector<std::vector<int>> &adj_list, int M, int components[]) {
    int visited[V];
    int counter = 1;
    int flag, cur_u, flag_size = 0;
    struct Stack TopSort;
    for (int i = 0; i < V; i++) {
        visited[i] = -1;
    };
    for (int i = 0; i < V; i++) {
        if (visited[i] == -1) {
            DFS(V, adj_list, i, visited, TopSort);
        }
    }
    while (!Is_empty(&TopSort)) {
        counter++;
        cur_u = Pop(&TopSort);
        components[cur_u] = counter - 1;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, u, v, i;
    std::vector<std::vector<int> > adj_list;
    std::cin >> N >> M;
    int components[N];
    adj_list.resize(N);
    for (i = 0; i < M; i++) {
        std::cin >> u >> v;
        if (u != v) {
            adj_list[u - 1].push_back(v - 1);
        }
    }
    FindPath(N, adj_list, M, components);
    for (i = 0; i < N; i++) {
        std::cout << components[i] << " ";
    }
}
