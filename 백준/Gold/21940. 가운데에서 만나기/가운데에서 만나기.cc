#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e9;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> times(N + 1, vector<int>(N + 1, INF));

    for (int i = 1; i <= N; i++) {
        times[i][i] = 0;
    }

    for (int i = 0; i < M; i++) {
        int A, B, T;
        cin >> A >> B >> T;
        times[A][B] = T;
    }

    int K;
    cin >> K;

    vector<int> friends(K);

    for (int i = 0; i < K; i++) {
        cin >> friends[i];
    }

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                times[i][j] = min(times[i][j], times[i][k] + times[k][j]);
            }
        }
    }

    map<int, vector<int>> candidates;
    
    for (int city = 1; city <= N; city++) {
        int maxTime = 0;
        
        for (int person : friends) {
            maxTime = max(maxTime, times[person][city] + times[city][person]);
        }

        candidates[maxTime].push_back(city);
    }

    // map은 key 기준 오름차순 정렬이므로, begin()이 최솟값 key를 가리킴
    auto it = candidates.begin();
    vector<int> answers = it->second;

    for (int answer : answers) {
        cout << answer << " ";
    }
    
    return 0;
}