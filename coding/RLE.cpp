#include <iostream>
void CheckPrevious(int Bt[][4], int index, int &index_root) {
    if (index_root == index) {
        return;
    }
    int npp;
    int np = Bt[index][3];
    if (np == -1) {
        return;
    }
    
    if (Bt[np][3] != -1) {
        npp = Bt[np][3];
        if (Bt[npp][0] == np) {
            Bt[npp][0] = index;
        }
        else {
            Bt[npp][2] = index;
        }
        Bt[index][3] = npp;
    }
    else {
        index_root = index;
        Bt[index][3] = -1;
    }
    
    if (Bt[np][0] == index) {
        Bt[np][0] = Bt[index][0];
        if (Bt[np][0] != -1) {
            Bt[Bt[np][0]][3] = np;
        }
        Bt[index][0] = np;
        Bt[np][3] = index;
    }
    else {
        Bt[np][2] = Bt[index][2];
        if (Bt[np][2] != -1) {
            Bt[Bt[np][2]][3] = np;
        }
        Bt[index][2] = np;
        Bt[np][3] = index;
    }
}

void Postordertraversal(int Bt[][4], int current, int &i, int array[]) {
    if (current != -1) {
        Postordertraversal(Bt, Bt[current][0], i, array);
        Postordertraversal(Bt, Bt[current][2], i, array);
        array[i] = Bt[current][1];
        i++;
    }
}

void PostordertraversalSymb(int Bt[][4], int current, int &i, char array[]) {
    if (current != -1) {
        PostordertraversalSymb(Bt, Bt[current][0], i, array);
        PostordertraversalSymb(Bt, Bt[current][2], i, array);
        array[i] = (char)Bt[current][1];
        i++;
    }
}

int main() {
    int n_coef, Q_coef, n_letters, Q_letters, i;
    int number;
    char letter;
    std::string decoded_message;
    std::cin >> n_coef >> Q_coef;
    int Bt_coef[n_coef][4];
    unsigned char let;
    int index_root_coef = 0;
    int index_root_letters = 0;
    for (i = 0; i < n_coef; i++) {
        std::cin >> number;
        Bt_coef[i][1] = number;
        Bt_coef[i][0] = -1;
        Bt_coef[i][2] = -1;
        Bt_coef[i][3] = -1;
        if (i != 0) {
            if (i % 2 != 0) {
                Bt_coef[(i - 1) / 2][0] = i;
            } else {
                Bt_coef[(i - 1) / 2][2] = i;
            }
            Bt_coef[i][3] = (i - 1) / 2;
        }
    }
    for (i = 0; i < Q_coef; i++) {
        std::cin >> number;
        CheckPrevious(Bt_coef, number - 1, index_root_coef);
    }
    
    std::cin >> n_letters >> Q_letters;
    int Bt_letters[n_letters][4];
    for (i = 0; i < n_letters; i++) {
        std::cin >> letter;
        let = letter;
        Bt_letters[i][1] = (int)let;
        Bt_letters[i][0] = -1;
        Bt_letters[i][2] = -1;
        Bt_letters[i][3] = -1;
        if (i != 0) {
            if (i % 2 != 0) {
                Bt_letters[(i - 1) / 2][0] = i;
            } else {
                Bt_letters[(i - 1) / 2][2] = i;
            }
            Bt_letters[i][3] = (i - 1) / 2;
        }
    }
    for (i = 0; i < Q_letters; i++) {
        std::cin >> number;
        CheckPrevious(Bt_letters, number - 1, index_root_letters);
    }
    
    int coef_ar[n_coef];
    char letters_ar[n_letters];
    int first_iterator = 0;
    int second_iterator = 0;
    Postordertraversal(Bt_coef, index_root_coef, first_iterator, coef_ar);
    PostordertraversalSymb(Bt_letters, index_root_letters, second_iterator, letters_ar);
    for (int k = 0; k < n_letters; k++) {
        for (int j = 0; j < coef_ar[k]; j++) {
            decoded_message += letters_ar[k];
        }
    }
    std::cout << decoded_message;
    return 0;
}
