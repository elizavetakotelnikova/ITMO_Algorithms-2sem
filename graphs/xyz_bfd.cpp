#include <iostream>
struct Node {
    int data[3];
    Node *next;
    Node(int value[])
    {
        data[0] = value[0];
        data[1] = value[1];
        data[2] = value[2];
        next = nullptr;
    }
};

struct Queue {
    Node *head = nullptr, *tail = nullptr;
};

void Enqueue(Queue *Q, int value[])
{
    Node *new_node = new Node(value);
    if (Q->tail == nullptr) {
        Q->head = Q->tail = new_node;
        return;
    }
    Q->tail->next = new_node;
    Q->tail = new_node;
};

int* Dequeue(Queue *Q)
{
    if (Q->head == nullptr)
        return nullptr;
    int* el = new int[3];
    el[0] = Q->head->data[0];
    el[1] = Q->head->data[1];
    el[2] = Q->head->data[2];
    Node *for_delete = Q->head;
    Q->head = Q->head->next;
    if (Q->head == nullptr)
        Q->tail = nullptr;
    delete (for_delete);
    return el;
};

bool Is_empty(Queue *Q) {
    if (Q->head == nullptr) {
        return true;
    }
    return false;
};

void Check(int x, int y, int z, int p_x, int p_y, int p_z, int &used_energy, Queue &Q, int source[], int distance[101][101][101]) {
    if (distance[x][y][z] == -1) {
        distance[x][y][z] = distance[p_x][p_y][p_z] + 1;
        used_energy = distance[p_x][p_y][p_z] + 1;
        source[0] = x;
        source[1] = y;
        source[2] = z;
        Enqueue(&Q, source);
    }
}; 

int BFS(int matrix[101][101][101], int st_x, int st_y, int st_z, int fin_x, int fin_y, int fin_z, int energy, int distance[101][101][101]) {
    int source[3];
    int used_energy;
    used_energy = 0;
    struct Queue Q;
    distance[st_x][st_y][st_z] = 0;
    source[0] = st_x;
    source[1] = st_y;
    source[2] = st_z;
    Enqueue(&Q, source);
    while (!Is_empty(&Q)) {
        int *u = Dequeue(&Q);
        if (distance[fin_x][fin_y][fin_z] != -1) {
            return distance[fin_x][fin_y][fin_z];
        }
        if (used_energy > energy) {
            return -1;
        }
        int i = u[0];
        int j = u[1];
        int k = u[2];
        if (i != 0) {
            if (matrix[i - 1][j][k] != -1) {
                    Check(i - 1, j, k, i, j, k, used_energy, Q, source, distance);
            }
        }
        if (i < 100) {
            if  (matrix[i+1][j][k] != -1) {
                Check(i+1, j, k, i, j, k, used_energy, Q, source, distance);
            }
        }
        if (j != 0) {
            if (matrix[i][j - 1][k] != -1) {
                Check(i, j - 1, k, i, j, k, used_energy, Q, source, distance);
            }
        }
        if (j < 100) {
            if (matrix[i][j + 1][k] != -1) {
                Check(i, j + 1, k, i, j, k, used_energy, Q, source, distance);
            }
        }
        if (k != 0) {
            if (matrix[i][j][k - 1] != -1) {
                Check(i, j, k - 1, i, j, k, used_energy, Q, source, distance);
            }
        }
        if (k < 100) {
            if (matrix[i][j][k + 1] != -1) {
                Check(i, j, k + 1, i, j, k, used_energy, Q, source, distance);
                }
        }
        free(u);
    }
    int k = distance[fin_x][fin_y][fin_z];
    return k;
}

int main() {
    int result, i, j, k, K, h, energy, st_x, st_y, st_z, fin_x, fin_y, fin_z, x, y, z;
    int matrix[101][101][101];
    int distance[101][101][101];
    std::cin >> K >> energy;
    std::cin >> st_x >> st_y >> st_z;
    std::cin >> fin_x >> fin_y >> fin_z;
    for (i = 0; i <= 100; i++) {
        for (j = 0; j <= 100; j++) {
            for (k = 0; k <= 100; k++) {
                matrix[i][j][k] = 1;
                distance[i][j][k] = -1;
            }
        }
    }
    if ((st_x == fin_x) and (st_y == fin_y) and (st_z == fin_z)) {
        std::cout << 0;
        return 0;
    }
    if (energy == 0) {
        std::cout << -1;
        return 0;
    }
    for (i = 0; i < K; i++) {
        std::cin >> x >> y >> z >> h;
        for (j = z; j < (z + h); j++) {
            if (((st_x == i) and (st_y == j) and (st_z == j)) or ((fin_x == i) and (fin_y == j) and (fin_z == j)))  {
                std::cout << -1;
                return 0;
            }
            matrix[x][y][j] = -1;
        }
    };
    result = BFS(matrix, st_x, st_y, st_z, fin_x, fin_y, fin_z, energy, distance);
    if ((result == -1) or (result > energy)) {
        std::cout << -1;
    }
    else {
        std::cout << result;
    }
}
