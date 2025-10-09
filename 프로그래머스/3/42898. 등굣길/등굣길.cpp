#include <string>
#include <vector>

using namespace std;

const int MOD = (int) 1e9 + 7;
const int PUDDLE = MOD + 1;

int solution(int m, int n, vector<vector<int>> puddles) {   
    pair<int, int> home(1, 1);
    pair<int, int> school(m, n);
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // 물에 잠긴 칸 표시
    for (vector<int>& puddle : puddles) {
        dp[puddle[0]][puddle[1]] = PUDDLE;
    }
    
    // 다이나믹 프로그래밍 수행
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == home.first && j == home.second) { // 집이 있는 좌표
                dp[i][j] = 1;
            } else if (dp[i][j] == PUDDLE) { // 물에 잠긴 좌표
                dp[i][j] = 0;
            } else { // 그 외 좌표
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
            }
        }
    }

    return dp[school.first][school.second];
}