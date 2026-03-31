#include <bits/stdc++.h>

using namespace std;

struct Node {
    int number; // 노드 번호
    vector<Node*> children; // 자식 노드

    Node(int number) : number(number) {}

    // 자식 노드 추가
    void addChild(Node* child) {
        children.push_back(child);
    }
};

const int MAX_N = (int)1e5;
const int INIT_SIZE = 0;

int N, R, Q;
ostringstream oss;
vector<vector<int>> edges(MAX_N + 1, vector<int>());
vector<Node*> nodes(MAX_N + 1);
vector<int> subtreeSizes(MAX_N + 1);

// 프로토타입
void makeTree(int curr, int parent);
int getSubtreeSize(int curr);

int main() {
    // 빠른 입출력 설정
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> R >> Q;

    // 트리 간선 정보 저장
    for (int i = 0; i < N - 1; i++) {
        int U, V;
        cin >> U >> V;

        edges[U].push_back(V);
        edges[V].push_back(U);
    }

    for (int i = 1; i <= N; i++) {
        nodes[i] = new Node(i);
    }

    // 트리 생성
    makeTree(R, -1);
    
    // 쿼리 수행
    for (int i = 0; i < Q; i++) {
        int U;
        cin >> U;

        oss << getSubtreeSize(U) << "\n";
    }

    cout << oss.str();
    
    return 0;
}

// 재귀적으로 트리 생성
void makeTree(int curr, int parent) {
    for (int next : edges[curr]) {
        if (next == parent) continue; // 부모 -> 자식 방향으로만 전개

        nodes[curr]->addChild(nodes[next]);
        makeTree(next, curr);
    }
}

// curr 노드를 루트로 하는 서브트리 크기 반환
int getSubtreeSize(int curr) {
    // 이미 계산 완료된 경우 메모이제이션 값 반환
    if (subtreeSizes[curr] != INIT_SIZE) {
        return subtreeSizes[curr];
    }

    vector<Node*> currChildren = nodes[curr]->children;

    // 리프 노드인 경우
    // 자기 자신만 서브트리에 포함되므로 1 저장 후 반환
    if (currChildren.size() == 0) {
        return subtreeSizes[curr] = 1;
    }

    // 리프 노드가 아닌 경우 
    // 자식 노드들의 서브트리 크기 합 + 1 저장 후 반환
    int count = 1;

    for (const auto& child : currChildren) {
        count += getSubtreeSize(child->number);
    }

    return subtreeSizes[curr] = count;
}