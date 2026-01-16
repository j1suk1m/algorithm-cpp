#include <bits/stdc++.h>

using namespace std;

// 인접 리스트에서 사용할 구조체
struct Edge {
    int dest;
    int cost;

    Edge(int dest, int cost) {
        this->dest = dest;
        this->cost = cost;
    }
};

// 다익스트라에서 사용할 구조체
struct State {
    int node;
    long long dist; // 누적 거리 -> int 오버플로 방지

    State(int node, long long dist) {
        this->node = node;
        this->dist = dist;
    }

    bool operator<(const State& other) const {
        return dist > other.dist;
    }
};

const int MAX_N = (int)1e5;
const int MAX_M = (int)1e5 * 5;
const int MAX_K = MAX_N;
const int MAX_C = (int)1e5;
const long long INF = (long long)MAX_M * MAX_C + 1;

int N, M, K;
vector<vector<Edge>> edges(MAX_N + 1, vector<Edge>()); // 인접 리스트
vector<int> interviewSites(MAX_K); // 면접장이 배치된 도시 번호
vector<long long> dist(MAX_N + 1, INF); // 도시별 가장 가까운 면접장까지의 최단 거리

void dijkstra(const vector<int>& sources);

int main() {
    cin >> N >> M >> K;

    // 인접 리스트 저장
    for (int i = 0; i < M; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;

        // 면접장에서 도시 방향으로 탐색하기 위해 간선을 거꾸로 저장
        edges[to].push_back(Edge(from, cost));
    }

    // 면접장이 배치된 도시 번호 저장
    for (int i = 0; i < K; i++) {
        cin >> interviewSites[i];
    }

    // 도시별 가장 가까운 면접장까지의 최단 거리 계산
    dijkstra(interviewSites);

    int farthestCity = 1; // 면접장까지 거리가 가장 먼 도시 번호
    long long farthestDist = 0LL; // 해당 도시에서 면접장까지의 거리

    for (int city = 1; city <= N; city++) {
        if (farthestDist < dist[city]) {
            farthestCity = city;
            farthestDist = dist[city];
        }
    }

    cout << farthestCity << "\n" << farthestDist;

    return 0;
}

void dijkstra(const vector<int>& sources) {
    priority_queue<State> pq;

    // 면접장 초기 방문
    for (int src : sources) {
        dist[src] = 0LL;
        pq.push(State(src, dist[src]));
    }

    while (!pq.empty()) {
        State curr = pq.top(); pq.pop();

        // 이미 최단 거리가 확정된 경우 무시
        if (dist[curr.node] < curr.dist) {
            continue;
        }

        for (const Edge& edge : edges[curr.node]) {
            if (dist[edge.dest] > curr.dist + edge.cost) {
                dist[edge.dest] = curr.dist + edge.cost;
                pq.push(State(edge.dest, dist[edge.dest]));
            }
        }
    }
}