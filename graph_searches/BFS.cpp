#include <iostream>
#include <vector>
struct Node {
    int data;
    Node *next;
    Node(int value)
    {
        data = value;
        next = NULL;
    }
};

struct Queue {
    Node *head = NULL, *tail = NULL;
};

void Enqueue(Queue *Q, int value)
{
    Node *new_node = new Node(value);
    if (Q->tail == NULL) {
        Q->head = Q->tail = new_node;
        return;
    }
    Q->tail->next = new_node;
    Q->tail = new_node;
};

int Dequeue(Queue *Q)
{
    if (Q->head == NULL)
        return -1;
    int el = Q->head->data;
    Node *for_delete = Q->head;
    Q->head = Q->head->next;
    if (Q->head == NULL)
        Q->tail = NULL;
    delete (for_delete);
    return el;
}
bool Is_empty(Queue *Q) {
    if (Q->head == NULL) {
        return true;
    }
    return false;
}
int BFS(int V, std::vector<std::vector<int>> &adj_list, int source, int destination) {
    int distance[V], u;
    for (int i = 0; i < V; i++) {
        distance[i] = -1;
    };
    struct Queue Q;
    distance[source - 1] = 0;
    Enqueue(&Q, source - 1);
    while (!Is_empty(&Q)) {
        u = Dequeue(&Q);
        for (int i = 0; i < adj_list[u].size(); i++) {
                if (distance[adj_list[u][i]] == -1) {
                    distance[adj_list[u][i]] = distance[u] + 1;
                    Enqueue(&Q, adj_list[u][i]);
                }
            }
        }
    return distance[destination - 1];
}

int main() {
    int N, M, u, v, source, dest, result, i;
    std::cin >> N >> M;
    std::vector<std::vector<int> > adj_list;
    adj_list.resize(N);
    for (i = 0; i < M; i++) {
        std::cin >> u >> v;
        adj_list[u - 1].push_back(v - 1);
        adj_list[v - 1].push_back(u - 1);
    }
    std::cin >> source >> dest;
    result = BFS(N, adj_list, source, dest);
    std::cout << result;
}
