#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int x;
    int y;
    int breakCount; // 지금까지 벽을 부순 횟수
    int dist;

    Node(int x, int y, int breakCount, int dist) {
        this->x = x;
        this->y = y;
        this->breakCount = breakCount;
        this->dist = dist;
    }
};

const int WALL = 1;

const vector<pair<int, int>> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int N, M, K;
vector<vector<int>> maps(1001, vector<int>(1001));
vector<vector<vector<bool>>> visited(11, vector<vector<bool>>(1001, vector<bool>(1001, false)));

int main() {
    cin >> N >> M >> K;

    // 지도 저장
    for (int i = 1; i <= N; i++) {
        string line;
        cin >> line;

        for (int j = 1; j <= M; j++) {
            maps[i][j] = line[j - 1] - '0';
        }
    }

    queue<Node> Q;

    Q.push(Node(1, 1, 0, 1));
    visited[0][1][1] = true; // 벽을 0번 부순 상태로 (1, 1) 방문

    int answer = -1;

    while (!Q.empty()) {
        auto [x, y, breakCount, dist] = Q.front(); Q.pop();

        // 종료 지점에 도착한 경우 최단 경로 반환
        if (x == N && y == M) {
            answer = dist;
            break;
        }

        // 상하좌우로 인접한 칸 이동
        for (const auto& [dx, dy] : dr) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx < 1 || nx > N || ny < 1 || ny > M) continue;

            if (maps[nx][ny] == WALL) { // 다음 칸이 벽인 경우 -> 부숴야만 해당 칸 방문 가능
                if (breakCount < K && !visited[breakCount + 1][nx][ny]) { // 벽을 부술 수 있어서 부순 경우
                    Q.push(Node(nx, ny, breakCount + 1, dist + 1));
                    visited[breakCount + 1][nx][ny] = true;
                }
            } else { // 다음 칸이 빈칸인 경우 -> 부수지 않아도 해당 칸 방문 가능
                if (!visited[breakCount][nx][ny]) {
                    Q.push(Node(nx, ny, breakCount, dist + 1));
                    visited[breakCount][nx][ny] = true;
                }
            }
        }
    }

    cout << answer;
    
    return 0;
}