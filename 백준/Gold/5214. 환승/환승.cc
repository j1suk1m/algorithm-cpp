#define Node pair<int, int>
#define STATION first
#define COUNT second

#include <bits/stdc++.h>

using namespace std;

int N, K, M;

// 프로토타입
bool isHypertube(int);
int getMinStationCount(const vector<vector<int>>&, int, int);

int main() {
    cin >> N >> K >> M;

    vector<vector<int>> graph(N + M + 1);

    // 하이퍼튜브 정보 저장
    for (int hypertube = N + 1; hypertube <= N + M; hypertube++) {
        for (int i = 0; i < K; i++) {
            int station;
            cin >> station;

            // 하이퍼튜브를 별도의 노드로 간주
            // 인접한 역과 양방향 연결
            graph[hypertube].push_back(station);
            graph[station].push_back(hypertube);
        }
    }

    int start = 1;
    int end = N;
    
    cout << getMinStationCount(graph, start, end);
    
    return 0;
}

// 노드 curr가 하이퍼튜브인지 확인
bool isHypertube(int curr) {
    return N + 1 <= curr && curr <= N + M;
}

// 너비 우선 탐색으로 노드 start부터 노드 end까지의 최소 역 개수 계산
int getMinStationCount(const vector<vector<int>>& graph, int start, int end) {
    queue<Node> Q;
    vector<bool> visited(N + M + 1, false);

    Q.push(make_pair(start, 1));
    visited[start] = true;

    while (!Q.empty()) {
        Node curr = Q.front(); Q.pop();

        // 종착역 도착
        if (curr.STATION == end) {
            return curr.COUNT;
        }

        for (int next : graph[curr.STATION]) {
            if (!visited[next]) {
                int nextCount = isHypertube(next) ? curr.COUNT + 1 : curr.COUNT;
                Q.push(make_pair(next, nextCount));
                visited[next] = true;
            }
        }
    }

    return -1;
}