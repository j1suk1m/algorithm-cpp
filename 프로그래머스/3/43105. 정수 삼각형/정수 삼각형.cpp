#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> triangle) {
    int n = (int)triangle.size();
    vector<vector<int>> dp(n);
    
    for (int i = 0; i < n; i++) {
        dp[i].resize(i + 1);
    }
    
    // 기저 조건
    dp[0][0] = triangle[0][0];
    
    // 다이나믹 프로그래밍 수행
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j <= i; j++) {
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + triangle[i + 1][j]);
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + triangle[i + 1][j + 1]);
        }
    }
    
    int answer = 0;
    
    // 마지막 행의 최댓값 계산
    for (int j = 0; j < n; j++) {
        answer = max(answer, dp[n - 1][j]);
    }
    
    return answer;
}