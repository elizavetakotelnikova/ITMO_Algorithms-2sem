#include <iostream>
#include <string>
#include <vector>
#include <utility>
void FillVector(std::string message, int len, std::vector <std::pair<char,int>> &dict, int &sum) {
    int count = 0;
    std::string prev_number;
    char prev;
    for (int i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            if (i != 0) {
                count = stoi(prev_number);
                sum += count;
                dict.emplace_back(prev, count);
            }
            prev = message[i];
            prev_number = "";
        }
        else {
            prev_number += message[i];
        }
    };
    count = stoi(prev_number);
    sum += count;
    dict.emplace_back(prev, count);
}

int FindNumber(std::string message, int &index) {
    std::string amount;
    while ((index < message.length()) && (isdigit(message[index]))) {
        amount += message[index];
        index++;
    }
    return stoi(amount);
}

int CheckDifference(std::string &first_message, std::string &second_message, int k) {
    std::vector <std::pair<char,int>> dict_fm;
    std::vector <std::pair<char,int>> dict_sm;
    int i = 0, j = 0, sum_one = 0, sum_two = 0;
    int diff = 0;
    FillVector(first_message, first_message.length(), dict_fm, sum_one);
    if (sum_one < k) {
        std::cout << "Yes";
        exit(0);
    }
    FillVector(second_message, second_message.length(), dict_sm, sum_two);
    while (i < dict_fm.size() and j < dict_sm.size()) {
        if (diff >= k) {
            std::cout << "No";
            exit(0);
        }
        if (dict_fm[i] != dict_sm[j]) {
            if (dict_fm[i].first != dict_sm[j].first) {
                diff += std::min(dict_fm[i].second, dict_sm[j].second);
            }
        }
        if (dict_fm[i].second < dict_sm[j].second) {
            dict_sm[j].second -= dict_fm[i].second;
            i++;
        }
        else if (dict_fm[i].second > dict_sm[j].second)
        {
            dict_fm[i].second -= dict_sm[j].second;
            j++;
        }
        else {
            i++;
            j++;
        }
    }
    return diff;

}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, k;
    std::string M_str;
    std::string S_str;
    std::cin >> n >> m >> k;
    std::cin >> M_str >> S_str;;
    if (k <= 0) {
        std::cout << "No";
        return 0;
    }
    if (CheckDifference(M_str, S_str, k) < k) {
        std::cout << "Yes";
    }
    else {
        std::cout << "No";
    }
    return 0;
}
