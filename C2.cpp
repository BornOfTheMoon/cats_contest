#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
 
int main() {
    freopen("input.txt", "r", stdin);
    int n, k;
    cin >> n >> k;
    vector<long long> arr(n);
    vector<long long> sums(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sums[i] = arr[i];
        if (i > 0) {
            sums[i] += sums[i - 1];
        }
    }
 
    vector<long long> right_edge(n, -1), answer_sums(n, INT64_MIN);
    map<int, int> uniq_numbers;
    for (int l = 0, r = 0; l < n; l++) {
        while (uniq_numbers.size() < k && r < n) {
            uniq_numbers[arr[r]]++;
            r++;
        }
        if (uniq_numbers.size() >= k) {
            right_edge[l] = r - 1;
            answer_sums[l] = sums[right_edge[l]];
            if (l > 0) {
                answer_sums[l] -= sums[l - 1];
            }
        }
        if (l < r) {
            uniq_numbers[arr[l]]--;
            if (uniq_numbers[arr[l]] == 0) {
                uniq_numbers.erase(arr[l]);
            }
        }
    }

    long long answer = INT64_MIN, answer_index;
    vector<long long> max_sum(n, INT64_MIN), max_sum_index(n);
    for (int i = n - 1; i >= 0; i--) {
        if (max_sum[i] < sums[i]) {
            max_sum[i] = sums[i];
            max_sum_index[i] = i;
        }
        if (i > 0) {
            max_sum[i - 1] = max_sum[i];
            max_sum_index[i - 1] = max_sum_index[i];
 
            if (right_edge[i] != -1 && answer_sums[i] < max_sum[right_edge[i]] - sums[i - 1]) {
                answer_sums[i] = max_sum[right_edge[i]] - sums[i - 1];
                right_edge[i] = max_sum_index[right_edge[i]];
            }
        }
        else {
            if (right_edge[i] != -1 && answer_sums[i] < max_sum[right_edge[i]]) {
                answer_sums[i] = max_sum[right_edge[i]];
                right_edge[i] = max_sum_index[right_edge[i]];
            }
        }
    }
 
    for (int i = 0; i < n; i++) {
        if (answer < answer_sums[i]) {
            answer = answer_sums[i];
            answer_index = i;
        }
    }
 
    freopen("output.txt", "w", stdout);
    (answer == INT64_MIN) ? cout << "IMPOSSIBLE" : cout << answer << "\n" << answer_index + 1 << " " << right_edge[answer_index] + 1;

    return 0;
}
