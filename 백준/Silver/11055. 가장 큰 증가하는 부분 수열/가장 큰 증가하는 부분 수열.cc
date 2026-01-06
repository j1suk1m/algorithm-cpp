#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, element;
    vector<int> sequence;

    cin >> N;

    // 수열 저장
    for (int i = 0; i < N; i++) {
        cin >> element;
        sequence.push_back(element);
    }

    vector<int> table;
    
    for (int i = 0; i < N; i++) {
        table.push_back(sequence[i]);      
    }
    
    // 다이나믹 프로그래밍
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (sequence[i] > sequence[j]) {
                table[i] = max(table[i], table[j] + sequence[i]);
            }
        }
    }

    cout << *max_element(table.begin(), table.end());
    
    return 0;
}