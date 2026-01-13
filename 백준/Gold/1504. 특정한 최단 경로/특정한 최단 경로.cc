#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int node;
    int distance;

    Edge(int node, int distance) {
        this->node = node;
        this->distance = distance;
    }

    bool operator<(const Edge& other) const {
        return distance > other.distance;
    }
};

const int INF = (int)1e9 * 2 + 1;
const int UNREACHABLE = -1;

int N, E;
long long answer = INF;
vector<vector<Edge>> edges;

// 프로토타입
int findMinDistance(int src, int dest);
void simulate(const vector<int>& nodes);

int main() {
    cin >> N >> E;

    edges.assign(N + 1, vector<Edge>());

    // 인접 리스트 저장
    for (int i = 0; i < E; i++) {
        int v1, v2, distance;
        cin >> v1 >> v2 >> distance;

        // 양방향 연결
        edges[v1].push_back(Edge(v2, distance));
        edges[v2].push_back(Edge(v1, distance));
    }

    int v1, v2;
    cin >> v1 >> v2;

    int start = 1, end = N;

    // case 1: start -> v1 -> v2 -> end
    vector<int> nodes = {start, v1, v2, end};
    simulate(nodes);

    // case 2: start -> v2 -> v1 -> end
    nodes = {start, v2, v1, end};
    simulate(nodes);

    cout << (answer == INF ? UNREACHABLE : answer);
    
    return 0;
}

int findMinDistance(int src, int dest) {
    priority_queue<Edge> PQ;
    vector<int> distances(N + 1, INF);

    PQ.push(Edge(src, 0));
    distances[src] = 0;

    while (!PQ.empty()) {
        auto [curr, currDistance] = PQ.top(); PQ.pop();

        if (distances[curr] < currDistance) {
            continue;
        }

        for (const auto& [next, nextDistance] : edges[curr]) {
            if (distances[next] > currDistance + nextDistance) {
                PQ.push(Edge(next, currDistance + nextDistance));
                distances[next] = currDistance + nextDistance;
            }
        }
    }

    return distances[dest];
}

void simulate(const vector<int>& nodes) {
    long long sum = 0LL;
    
    for (int i = 0; i < (int)nodes.size() - 1; i++) {
        int src = nodes[i];
        int dest = nodes[i + 1];

        int result = findMinDistance(src, dest);

        if (result == INF) {
            return;
        }

        sum += result;
    }

    answer = min(answer, sum);
}