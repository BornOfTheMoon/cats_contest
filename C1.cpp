#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int get_best_result(vector<vector<int>> participant, int n, int m, vector<int> count_enemies) {
    sort(participant.begin(), participant.end());
    vector<int> count(m);
    int best_difference = 0, result = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (participant[i][2] == 2) {
            count[participant[i][1]]++;
        } else {
            int current_score = 2 * count[participant[i][1]] - count_enemies[participant[i][1]];
            result += current_score;
            for (int j = 0; j < m; j++) {
                if (j != participant[i][1]) {
                    best_difference = max(best_difference, 2 * count[j] - count_enemies[j] - current_score);
                }
            }
        }
    }
    return result + best_difference;
}

int main() {
    ifstream fin;
    fin.open("input.txt");
    int n, m, level, weight;
    fin >> n >> m;
    vector<vector<int>> participant;
    vector<int> count_enemies(m);
    for (int i = 0; i < n; i++) {
        fin >> level >> weight;
        participant.push_back({level, weight - 1, 1});
    }
    for (int i = 0; i < n; i++) {
        fin >> level >> weight;
        participant.push_back({level, weight - 1, 2});
        count_enemies[weight - 1]++;
    }
    fin.close();
    
    ofstream fout;
    fout.open("output.txt");
    fout << get_best_result(participant, n, m, count_enemies);
    fout.close();
}