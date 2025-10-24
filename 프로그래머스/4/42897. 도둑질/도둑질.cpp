#include <vector>
#include <algorithm>

#define FIRST_INCLUDED 0
#define FIRST_NOT_INCLUDED 1

using namespace std;

int solution(vector<int> money) {
    int houseCount = (int)money.size();
    
    // dp[FIRST_INCLUDED][n] = 첫번째 집을 도둑질하고 n번째 집까지 도달했을 때 최대 이익
    // dp[FIRST_NOT_INCLUDED][n] = 첫번째 집을 도둑질하지 않고 n번째 집까지 도달했을 때 최대 이익
    vector<vector<int>> dp(2, vector<int>(houseCount, 0));
    
    // DP 테이블 초기화
    for (int i = 0; i < houseCount; i++) {
        dp[FIRST_INCLUDED][i] = money[i];
        dp[FIRST_NOT_INCLUDED][i] = money[i];
    }
    
    // 기저 조건
    dp[FIRST_INCLUDED][0] = money[0]; // 첫번째 집 도둑질
    dp[FIRST_INCLUDED][1] = money[0]; // 인접한 두번째 집은 도둑질하지 않음
    
    dp[FIRST_NOT_INCLUDED][0] = 0; // 첫번째 집 도둑질하지 않음
    dp[FIRST_NOT_INCLUDED][1] = money[1]; // 두번째 집 도둑질
        
    // 다이나믹 프로그래밍
    for (int i = 2; i < houseCount - 1; i++) {
        dp[FIRST_INCLUDED][i] = max(
            dp[FIRST_INCLUDED][i - 1], 
            dp[FIRST_INCLUDED][i - 2] + money[i]
        );
    }
    
    for (int i = 2; i < houseCount; i++) {
        dp[FIRST_NOT_INCLUDED][i] = max(
            dp[FIRST_NOT_INCLUDED][i - 1], 
            dp[FIRST_NOT_INCLUDED][i - 2] + money[i]
        );
    }
    
    return max(
        dp[FIRST_INCLUDED][houseCount - 2], 
        dp[FIRST_NOT_INCLUDED][houseCount - 1]
    );
}