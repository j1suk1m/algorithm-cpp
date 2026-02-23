#include <bits/stdc++.h>

using namespace std;

enum Relation {
    UNKNOWN = -1,
    LIGHTER = 0,
    HEAVIER = 1
};

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<Relation>> relation(N + 1, vector<Relation>(N + 1, UNKNOWN));

    while (M-- > 0) {
        int m1, m2;
        cin >> m1 >> m2;

        // m1 > m2
        relation[m1][m2] = HEAVIER;
        relation[m2][m1] = LIGHTER;
    }

    // 플로이드 워셜 알고리즘 수행
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i == k || j == k) continue;
                if (relation[i][j] != UNKNOWN) continue;
                if (relation[i][k] == UNKNOWN || relation[k][j] == UNKNOWN) continue;

                // i > k이고 k > j이면 i > j
                if (relation[i][k] == HEAVIER && relation[k][j] == HEAVIER) {
                    relation[i][j] = HEAVIER;
                    relation[j][i] = LIGHTER;
                    continue;
                }

                // i < k이고 k < j이면 i < j
                if (relation[i][k] == LIGHTER && relation[k][j] == LIGHTER) {
                    relation[i][j] = LIGHTER;
                    relation[j][i] = HEAVIER;
                    continue;
                }
            }
        }
    }

    // 무게가 중간이 될 가능성이 있는 구슬 개수
    int midCandidateCount = 0;

    for (int m = 1; m <= N; m++) {
        int heavierCount = 0; // 구슬 m보다 무거운 구슬 개수
        int lighterCount = 0; // 구슬 m보다 가벼운 구슬 개수

        for (int i = 1; i <= N; i++) {
            if (i == m) continue;

            if (relation[i][m] == HEAVIER) {
                heavierCount++;
            } else if (relation[i][m] == LIGHTER) {
                lighterCount++;
            }
        }

        // 구슬 m의 무게가 전체 무게의 중간이 될 가능성이 있는지 검증
        if (heavierCount <= N / 2 && lighterCount <= N / 2) {
            midCandidateCount++;
        }
    }

    cout << N - midCandidateCount;
    
    return 0;
}