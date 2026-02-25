#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x;
    int time;

    Node(int x, int time) {
        this->x = x;
        this->time = time;
    }
};

const int MAX = (int)1e5;
const int INF = (int)1e6;

int N, K;

int main() {
    cin >> N >> K;

    deque<Node> dq;
    vector<int> times(MAX + 1, INF);

    dq.push_back(Node(N, 0));
    times[N] = 0;

    while (!dq.empty()) {
        Node curr = dq.front(); dq.pop_front();

        // 최단 시간을 갱신할 수 없는 경우 skip
        if (times[curr.x] < curr.time) {
            continue;
        }

        // case 1: 순간 이동
        if (2 * curr.x <= MAX && curr.time < times[2 * curr.x]) {
            dq.push_front(Node(2 * curr.x, curr.time));
            times[2 * curr.x] = curr.time;
        }

        // case 2: 걷기
        for (int dx : {-1, 1}) {
            int nx = curr.x + dx;
            
            if (nx < 0 || nx > MAX || times[nx] <= curr.time + 1) {
                continue;
            }

            dq.push_back(Node(nx, curr.time + 1));
            times[nx] = curr.time + 1;
        }
    }

    cout << times[K];
    
    return 0;
}