#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
    ifstream fin;
    fin.open("input.txt");
    int n;
    fin >> n;
    int* nails = new int[n];
    int* distance = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> nails[i];
    }
    fin.close();
    sort(&nails[0], &nails[n]);
    distance[1] = nails[1] - nails[0];
    distance[2] = (nails[2] - nails[1]) + distance[1];
    for (int i = 3; i < n; i++) {
        distance[i] = (nails[i] - nails[i - 1]) + min(distance[i - 1], distance[i - 2]);
    }
    ofstream fout;
    fout.open("output.txt");
    fout << distance[n - 1];
    fout.close();
}