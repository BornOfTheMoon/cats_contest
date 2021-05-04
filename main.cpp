#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int search_place(long long number) {
    int place = -1;
    for (int i = 0; i < 11; i++) {
        number /= 10;
        place++;
        if (!number) {
            break;
        }        
    }
    return place;
}

int main() {
    ifstream fin;
    fin.open("input.txt");
    int n, m;
    fin >> n >> m;
    vector<int> thirst[11];
    int number;
    for (int i = 0; i < n; i++) {
        fin >> number;
        int place = search_place(number);
        thirst[place].push_back(number);
    }
    fin.close();
    for (int i = 10; m > 0 && i >= 0; i--) {
        if (thirst[i].empty()) {
            continue;
        }
        sort(thirst[i].begin(), thirst[i].end());
        while (!thirst[i].empty() && m > 0) {
            if (i > 0) {
                thirst[i - 1].push_back(thirst[i][thirst[i].size() - 1] / 10);
            }
            thirst[i].pop_back();
            m--;
        }
    }
    ofstream fout;
    fout.open("output.txt");
    long long sum = 0;
    for (int i = 0; i < 11; i++) {
        while (!thirst[i].empty()) {
            sum += thirst[i][thirst[i].size() - 1];
            thirst[i].pop_back();
        }
    }
    fout << sum;
    fout.close();
}