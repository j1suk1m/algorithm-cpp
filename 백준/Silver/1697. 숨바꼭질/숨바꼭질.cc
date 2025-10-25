#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int N, K;
    
    cin >> N >> K;

    // 이동할 필요가 없으면 early return
    if (N == K) {
        cout << 0;
        return 0;
    }

    bool visited[100001] = {false, };
    queue<pair<int, int>> q;

    q.push(make_pair(N, 0));
    visited[N] = true;

    while (!q.empty()) {
        auto [currPos, currTime] = q.front(); q.pop();

        // 종료 조건
        if (currPos == K) {
            cout << currTime;
            break;
        }

        // 다음 위치로 이동
        for (int move : {-1, 1, currPos}) {
            int nextPos = currPos + move;

            if (nextPos < 0 || nextPos > 100000) continue;
            if (visited[nextPos]) continue;
    
            q.push(make_pair(nextPos, currTime + 1));
            visited[nextPos] = true;
        }
    }
    
    return 0;
}