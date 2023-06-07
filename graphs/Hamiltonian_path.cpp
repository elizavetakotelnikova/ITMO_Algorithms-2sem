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

bool FindPath(int V, std::vector<std::vector<int>> &adj_list, int M) {
    int visited[V];
    int counter = 0;
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
    int start;
    start = TopSort.head->data;
    while (!Is_empty(&TopSort)) {
        cur_u = Pop(&TopSort);
        flag = 0;
        //std::cout << cur_u;
        if (TopSort.head != nullptr) {
            for (int i = 0; i < adj_list[cur_u].size(); i++) {
                if (adj_list[cur_u][i] == TopSort.head->data) {
                    flag = 1;
                }
                //std::cout << cur_u << " " << i;
            }
            if ((M == V - 1) and (flag_size <= 1)){
                for (int i = 0; i < adj_list[start].size(); i++) {
                    if (adj_list[start][i] == TopSort.head->data) {
                        flag_size++;
                        flag = 1;
                    }
                }
            }
            if (!flag) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, u, v, i;
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
    if (FindPath(N, adj_list, M)) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
}
