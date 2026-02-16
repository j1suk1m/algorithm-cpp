#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> parent; 
vector<int> truthKnowers; 
set<int> truthKnowerRoots; 
vector<vector<int>> parties;

// 프로토타입
void init(int);
int find(int);
void unite(int, int);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    int truthKnowerCount;
    cin >> truthKnowerCount;

    // 진실을 아는 사람 저장
    for (int i = 0; i < truthKnowerCount; i++) {
        int truthKnower;
        cin >> truthKnower;
        truthKnowers.push_back(truthKnower);
    }

    // 파티별 참석자 저장
    for (int i = 0; i < M; i++) {
        int participantCount;
        cin >> participantCount;
        parties.push_back(vector<int>(participantCount));
        
        for (int j = 0; j < participantCount; j++) {
            cin >> parties[i][j];
        }
    }

    // union-find 초기화
    init(N);

    // 같은 파티 참석자들은 서로 같은 집합으로 묶기
    for (const vector<int>& party : parties) {
        for (int i = 1; i < (int)party.size(); i++) {
            unite(party[0], party[i]);
        }
    }

    // 진실을 아는 사람들의 루트 저장
    for (int v : truthKnowers) {
        truthKnowerRoots.insert(find(v));
    }

    int count = 0;

    // 파티별 거짓말 가능 여부 검사
    for (const vector<int>& party : parties) {
        bool canLie = true;

        // 현재 파티 참석자 중 진실 그룹에 속하는 사람이 있는지 확인
        for (int v : party) {
            if (truthKnowerRoots.count(find(v))) {
                canLie = false;
                break;
            }
        }

        if (canLie) {
            count++;
        }
    }
    
    cout << count;
    
    return 0;
}

// 루트를 자기 자신으로 초기화
void init(int n) {
    parent.resize(n + 1, 0);

    for (int v = 1; v <= n; v++) {
        parent[v] = v;
    }
}

// 경로 압축 기반 루트 반환
int find(int v) {
    if (parent[v] != v) {
        parent[v] = find(parent[v]);
    }

    return parent[v];
}

// 두 사람을 같은 집합으로 묶기
void unite(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);

    if (rootU < rootV) {
        parent[rootV] = rootU;
    } else if (rootU > rootV) {
        parent[rootU] = rootV;
    }
}