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

void DFS_components(int V, std::vector<std::vector<int>> &adj_list, int u, int components[], int &counter) {
    components[u] = counter;
    for (int j : adj_list[u]) {
        if (components[j] == -1) {
            DFS_components(V, adj_list, j, components, counter);
        }
    }
}

void FindPath(int V, std::vector<std::vector<int>> &adj_list, std::vector<std::vector<int>> &adj_list_second, int M, int components[]) {
    int visited[V];
    int counter = 0, current;
    struct Stack TopSort;
    for (int i = 0; i < V; i++) {
        visited[i] = -1;
    };
    for (int i = 0; i < V; i++) {
        if (visited[i] == -1) {
            DFS(V, adj_list_second, i, visited, TopSort);
        }
    }
    counter = 0;
    for (int i = 0; i < V; i++) {
        components[i] = -1;
    };
    while (!Is_empty(&TopSort)) {
        counter++;
        current = Pop(&TopSort);
        if (components[current] == -1) {
            DFS_components(V, adj_list, current, components, counter);
            counter++;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, u, v, i, Q, first, second;
    std::vector<std::vector<int> > adj_list;
    std::vector<std::vector<int> > adj_list_second;
    std::cin >> N >> M >> Q;
    int components[N];
    adj_list.resize(N);
    adj_list_second.resize(N);
    for (i = 0; i < M; i++) {
        std::cin >> u >> v;
        if (u != v) {
            adj_list[u - 1].push_back(v - 1);
            adj_list_second[v - 1].push_back(u - 1);
        }
    }
    FindPath(N, adj_list, adj_list_second, M, components);
    for (int j = 0; j < Q; j++) {
        std::cin >> first >> second;
        if (components[first - 1] == components[second - 1]) {
            std::cout << "YES" << "\n";
        } else {
            std::cout << "NO" << "\n";
        }
    }
}
