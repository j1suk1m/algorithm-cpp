#include <bits/stdc++.h>

using namespace std;

const int INF = 1001;

int main() {
    int T, W;
    cin >> T >> W;

    vector<int> tree(T + 1);

    // 매초마다 자두가 떨어지는 나무의 번호 저장
    for (int t = 1; t <= T; t++) {
        cin >> tree[t];
    }

    // table[이동 횟수][나무 번호] = 자두 개수
    vector<vector<int>> table(W + 1, vector<int>(3));

    // 기저 조건
    table[0][1] = 0;
    table[0][2] = -INF;

    // 다이나믹 프로그래밍
    for (int t = 1; t <= T; t++) {
        for (int w = W; w >= 0; w--) {
            for (int p = 1; p <= 2; p++) {
                // 이동하지 않는 경우
                int stay = table[w][p];

                // 이동하는 경우
                int move = (w > 0) ? table[w - 1][3 - p] : -INF;

                table[w][p] = max(stay, move);

                if (tree[t] == p) {
                    table[w][p] += 1;
                }                
            }
        }
    }

    int answer = 0;

    // 최댓값 찾기
    for (int w = 0; w <= W; w++) {
        answer = max(answer, table[w][1]);
        answer = max(answer, table[w][2]);
    }

    cout << answer;
    
    return 0;
}