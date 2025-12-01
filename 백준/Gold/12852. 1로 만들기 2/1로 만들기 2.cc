#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = (int)1e6 + 1;

int main() {
    int N;

    cin >> N;

    vector<int> dp(N + 1, INF);
    vector<int> prev(N + 1, INF); 

    // 기저 조건
    dp[1] = 0;

    // 다이나믹 프로그래밍
    for(int curr = 2; curr <= N; curr++) {
        dp[curr] = dp[curr - 1] + 1;
        prev[curr] = curr - 1;
        
        if (curr % 3 == 0 && dp[curr] > dp[curr / 3] + 1) {
            dp[curr] = dp[curr / 3] + 1;
            prev[curr] = curr / 3;
        }

        if (curr % 2 == 0 && dp[curr] > dp[curr / 2] + 1) {
            dp[curr] = dp[curr / 2] + 1;
            prev[curr] = curr / 2;
        }
    }

    cout << dp[N] << "\n";

    int curr = N;

    // 역추적
    while (curr != INF) {
        cout << curr << ((curr > 1) ? " " : "");
        curr = prev[curr];
    }
    
    return 0;
}