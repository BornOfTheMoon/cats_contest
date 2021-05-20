#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int get_hash(int number) {
    return (number % 997);
}

void insert(vector<int>* map, int number) {
    int hash = get_hash(number);
    for (int i = 0; i < map[hash].size(); i++) {
        if (map[hash][i] == number) {
            return;
        }
    }
    map[hash].push_back(number);
    return;
}

void erase(vector<int>* map, int number) {
    int hash = get_hash(number);
    for (int i = 0; i < map[hash].size(); i++) {
        if (map[hash][i] == number) {
            map[hash][i] = map[hash][map[hash].size() - 1];
            map[hash].pop_back();
        }
    }
}

vector<int> map_to_vector(vector<int>* map) {
    vector<int> all_numbers;
    for (int i = 0; i < 997; i++) {
        for (int j = 0; j < map[i].size(); j++) {
            all_numbers.push_back(map[i][j]);
        }
    }
    sort(all_numbers.begin(), all_numbers.end());
    return all_numbers;
}

void print(vector<int>* map) {
    vector<int> all_numbers = map_to_vector(map);
    for (int i = 0; i < all_numbers.size(); i++) {
        cout << all_numbers[i] << " ";
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<int> map[997];
    int number;
    cin >> number;
    while (number != 0) {
        if (number > 0) {
            insert(map, number);
        } else {
            erase(map, -number);
        }
        cin >> number;
    }
    print(map);
}