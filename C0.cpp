#include <iostream>
#include <fstream>
using namespace std;

int* build_tree(int* arr, int left, int right, int position = 0) {
    static int* new_arr = new int[4 * (right + 1)];
    if (left == right) {
        new_arr[position] = arr[left];
    } else {
        int mid = (right + left) / 2;
        build_tree(arr, left, mid, 2 * position + 1);
        build_tree(arr, mid + 1, right, 2 * position + 2);
        new_arr[position] = (new_arr[2 * position + 1] > new_arr[2 * position + 2]) ? new_arr[2 * position + 1] : new_arr[2 * position + 2];
    }
    return new_arr;
}

int get_max(int* arr, int left, int right, int left_edge, int right_edge, int position = 0) {
    if (left == left_edge && right == right_edge) {
        return arr[position];
    }
    int result;
    int mid = (right + left) / 2;
    if (right_edge <= mid) {
        result = get_max(arr, left, mid, left_edge, right_edge, 2 * position + 1);
    } else if (left_edge > mid) {
        result = get_max(arr, mid + 1, right, left_edge, right_edge, 2 * position + 2);
    } else {
        int first_result = get_max(arr, left, mid, left_edge, mid, 2 * position + 1);
        int second_result = get_max(arr, mid + 1, right, mid + 1, right_edge, 2 * position + 2);
        result = (first_result > second_result) ? first_result : second_result;
    }
    return result;
}

int main() {
    ifstream fin;
    fin.open("input.txt");
    int n;
    fin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> arr[i];
    }
    int length;
    string steps;
    fin >> length >> steps;
    fin.close();
    int* new_arr = new int[4 * n];
    new_arr = build_tree(arr, 0, n - 1);

    int left_edge = 0;
    int right_edge = 0;

    ofstream fout;
    fout.open("output.txt");
    for (int i = 0; i < length; i++) {
        if (steps[i] == 'R') {
            right_edge++;
        } else {
            left_edge++;
        }
        fout << get_max(new_arr, 0, n - 1, left_edge, right_edge) << " ";
    }  
    fout.close(); 
}