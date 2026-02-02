#include <bits/stdc++.h>

using namespace std;

const int INF = 50;
const int END_OF_INPUT = -1;
const int DIRECT_FRIEND_DISTANCE = 1;

int main() {
    int memberCount;
    cin >> memberCount;

    // distances[i][j]: i번 회원에서 j번 회원까지의 최단 거리
    vector<vector<int>> distances(
        memberCount + 1, 
        vector<int>(memberCount + 1, INF)
    );

    int u, v;

    // 친구 관계 저장
    while (true) {
        cin >> u >> v;

        if (u == END_OF_INPUT && v == END_OF_INPUT) {
            break;
        }

        // 양방향 친구 관계
        distances[u][v] = DIRECT_FRIEND_DISTANCE;
        distances[v][u] = DIRECT_FRIEND_DISTANCE;
    }

    // 플로이드 워셜
    // 모든 회원 쌍 사이의 최단 거리 계산
    for (int k = 1; k <= memberCount; k++) {
        for (int i = 1; i <= memberCount; i++) {
            for (int j = 1; j <= memberCount; j++) {
                if (i == j) continue;
                
                distances[i][j] = min(
                    distances[i][j],
                    distances[i][k] + distances[k][j]
                );
            }
        }
    }

    // scores[i]: i번 회원의 점수 (가장 먼 회원까지의 거리)
    vector<int> scores(memberCount + 1, 0);

    // 회원별 점수 계산
    for (int from = 1; from <= memberCount; from++) {
        for (int to = 1; to <= memberCount; to++) {
            if (from == to || distances[from][to] == INF) continue;

            scores[from] = max(
                scores[from],
                distances[from][to]
            );
        }
    }

    // 회장 후보의 점수
    int minScore = INF; 

    for (int member = 1; member <= memberCount; member++) {
        minScore = min(minScore, scores[member]);
    }

    // 회장 후보 목록
    vector<int> candidates;

    for (int member = 1; member <= memberCount; member++) {
        if (scores[member] == minScore) {
            candidates.push_back(member);
        }
    }

    cout << minScore << " " << candidates.size() << "\n";

    for (int candidate : candidates) {
        cout << candidate << " ";
    }
    
    return 0;
}