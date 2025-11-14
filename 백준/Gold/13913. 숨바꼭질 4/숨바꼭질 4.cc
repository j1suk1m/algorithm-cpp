#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

const int NONE = -1;
const int MAX = 200001;

int main() {
    int N, K;

    cin >> N >> K;

    queue<int> Q;
    vector<int> visitTime(MAX, NONE); // 방문 시간
    vector<int> parent(MAX, NONE); // 역추적을 위한 부모 노드 저장

    Q.push(N);
    visitTime[N] = 0;

    while (!Q.empty()) {
        int curr = Q.front(); Q.pop();

        // 동생을 발견한 경우
        if (curr == K) {
            cout << visitTime[curr] << "\n";
            break;
        }

        // 다음 위치로 이동
        for (int next : {curr - 1, curr + 1, 2 * curr}) {
            if (next < 0 || next >= MAX) continue;
            if (visitTime[next] != NONE) continue;

            Q.push(next);
            visitTime[next] = visitTime[curr] + 1;
            parent[next] = curr;
        }
    }

    vector<int> path;
    int curr = K;

    // 역추적
    while (curr != NONE) {
        path.push_back(curr);
        curr = parent[curr];
    }

    reverse(path.begin(), path.end());

    ostringstream oss;

    // 문자열 재조립
    for (int i = 0; i < path.size(); i++) {
        if (i > 0) oss << ' ';
        oss << path[i];
    }

    cout << oss.str();
    
    return 0;
}