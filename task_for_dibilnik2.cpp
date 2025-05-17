#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

vector<int> merge_arrays(const vector<vector<int>>& arrays) {
    unordered_set<int> set;
    for (const auto& arr : arrays) {
        for (int num : arr) {
            set.insert(num);
        }
    }
    vector<int> res(set.begin(), set.end());
    sort(res.begin(), res.end());
    return res;
}   

int main() {
    vector<vector<int>> input = {
        {1, 5, 6, 3},
        {2, 1, 7, 3},
        {8, 3, 2}
    };
    vector<int> output = merge_arrays(input);
    for (int i = 0; i < output.size(); i++) {
        cout << output[i] <<" ";
    }
    cout << "\n";
}