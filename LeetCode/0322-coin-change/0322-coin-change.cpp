const int INF = (int)1e4 + 1; // 동전으로 금액을 만들 수 없는 경우를 나타내기 위한 충분히 큰 값
const int IMPOSSIBLE = -1;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) {
            return 0;
        }

        // dp[i]: 금액 i를 만들 수 있는 최소 동전 개수
        vector<int> dp(amount + 1, INF);

        // base case: 0원은 동전 0개로 만들 수 있음
        dp[0] = 0;

        // 1 ~ amount까지 각 금액을 만들 수 있는 최소 동전 개수 갱신
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                // 현재 동전을 사용해 갱신할 수 없는 경우 skip
                if (i < coin || dp[i - coin] == INF) {
                    continue;
                }

                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }

        if (dp[amount] == INF) {
            return IMPOSSIBLE;
        }

        return dp[amount];
    }
};