#include <bits/stdc++.h>

using namespace std;
using Road = pair<int, int>; // {node, time}

// 우선순위 큐에서 사용할 비교 함수
struct Compare {
    bool operator()(const Road& a, const Road& b) {
        if (a.second != b.second) {
            return a.second > b.second; // time 작은 순서
        }

        return a.first > b.first; // node 작은 순서
    }
};

const int INF = (int)1e7;

int N, M, X;
vector<vector<Road>> roads;

// 프로토타입
int findMinTime(int src, int dest);
int simulate(int v1, int v2);

int main() {
    cin >> N >> M >> X;

    roads.assign(N + 1, vector<Road>());

    // 인접 리스트 저장
    for (int i = 0; i < M; i++) {
        int start, end, time;
        cin >> start >> end >> time;

        // 단방향 연결
        roads[start].push_back({end, time});
    }

    int answer = 0;

    // 학생별 왕복 시간 계산
    for (int v = 1; v <= N; v++) {
        if (v == X) continue;

        int result = simulate(v, X);
        answer = max(answer, result); // 최댓값 갱신
    }

    cout << answer;
    
    return 0;
}

int findMinTime(int src, int dest) {
    priority_queue<Road, vector<Road>, Compare> PQ;
    vector<int> times(N + 1, INF);

    PQ.push({src, 0});
    times[src] = 0;

    while (!PQ.empty()) {
        auto [curr, currTime] = PQ.top(); PQ.pop();

        if (times[curr] < currTime) {
            continue;
        }

        for (const auto& [next, nextTime] : roads[curr]) {
            if (times[next] > currTime + nextTime) {
                PQ.push({next, currTime + nextTime});
                times[next] = currTime + nextTime;
            }
        }
    }

    return times[dest];
}

int simulate(int v1, int v2) {
    int totalTime = 0;

    // 왕복 시간 계산
    totalTime += findMinTime(v1, v2);
    totalTime += findMinTime(v2, v1);

    return totalTime;
}