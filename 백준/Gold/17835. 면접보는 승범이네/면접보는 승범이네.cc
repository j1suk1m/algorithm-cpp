#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int dest;
    long long distance;

    Edge(int dest, long long distance) {
        this->dest = dest;
        this->distance = distance;
    }

    bool operator<(const Edge& other) const {
        return distance > other.distance;
    }
};

const long long INF = (long long)1e5 * 1e5 * 5;

int N, M, K;
vector<int> multiSources; // 면접장이 배치된 도시 번호
vector<vector<Edge>> edges; // 인접 리스트
vector<long long> minDistances; // 도시별 가장 가까운 면접장까지의 최단 거리

// 프로토타입
void findMinDistances();

int main() {
    cin >> N >> M >> K;

    edges.assign(N + 1, vector<Edge>());

    // 인접 리스트 저장
    for (int i = 0; i < M; i++) {
        int src, dest;
        long long distance;
        cin >> src >> dest >> distance;

        // 단방향 연결
        // 멀티 소스 다익스트라 알고리즘을 적용하기 위해 간선을 거꾸로 저장
        edges[dest].push_back(Edge(src, distance));
    }

    multiSources.assign(K, 0);

    // 면접장이 배치된 도시 번호 저장
    for (int i = 0; i < K; i++) {
        cin >> multiSources[i];
    }

    minDistances.assign(N + 1, INF);

    // 도시별 가장 가까운 면접장까지의 최단 거리 계산
    findMinDistances();

    int farthestNode = 1;
    long long maxDistance = 0LL;
    
    for (int node = 1; node <= N; node++) {
        if (maxDistance < minDistances[node]) {
            farthestNode = node;
            maxDistance = minDistances[node];
        }
    }

    cout << farthestNode << "\n" << maxDistance;
    
    return 0;
}

void findMinDistances() {
    priority_queue<Edge> PQ;

    // 면접장 초기 방문
    for (int src : multiSources) {
        PQ.push(Edge(src, 0LL));
        minDistances[src] = 0;
    }

    while (!PQ.empty()) {
        auto [curr, currDistance] = PQ.top(); PQ.pop();

        if (minDistances[curr] < currDistance) {
            continue;
        }

        for (const auto& [next, nextDistance] : edges[curr]) {
            if (minDistances[next] > currDistance + nextDistance) {
                PQ.push(Edge(next, currDistance + nextDistance));
                minDistances[next] = currDistance + nextDistance;
            }
        }
    }
}