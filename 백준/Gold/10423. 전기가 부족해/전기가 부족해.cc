#include <bits/stdc++.h>

using namespace std;

struct Cable {
    int u;
    int v;
    int w;

    Cable(int u, int v, int w) {
        this->u = u;
        this->v = v;
        this->w = w;
    }
};

// 프로토타입
int find(vector<int>& parent, int v);
void unite(vector<int>& parent, int u, int v);

int main() {
    // 빠른 입출력 설정
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<int> powerStations(K);

    // 발전소가 설치된 도시 번호 저장
    for (int i = 0; i < K; i++) {
        cin >> powerStations[i];
    }

    vector<Cable> cables;

    // 케이블 정보 저장
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        cables.push_back(Cable(u, v, w));
    }

    vector<int> parent(N + 1);

    for (int v = 1; v <= N; v++) {
        parent[v] = v;
    }

    // 발전소가 설치된 도시를 같은 집합으로 묶기
    for (int i = 1; i < K; i++) {
        unite(parent, powerStations[0], powerStations[i]);
    }

    // 케이블 설치 비용 기준 오름차순 정렬
    sort(cables.begin(), cables.end(), [](const auto& c1, const auto& c2) {
        return c1.w < c2.w;
    });

    int answer = 0;

    // 케이블 설치
    for (const auto [u, v, w] : cables) {
        if (find(parent, u) != find(parent, v)) {
            unite(parent, u, v);
            answer += w;
        }
    }

    cout << answer;
    
    return 0;
}

int find(vector<int>& parent, int v) {
    if (parent[v] == v) {
        return v;
    }

    return parent[v] = find(parent, parent[v]);
}

void unite(vector<int>& parent, int u, int v) {
    int rootV = find(parent, v);
    int rootU = find(parent, u);
    
    if (rootU < rootV) {
        parent[rootV] = rootU;
    } else {
        parent[rootU] = rootV;
    }
}