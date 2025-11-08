#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int x;
    int y;
    bool hasBroken;
    int count;

    Node(int x, int y, bool hasBroken, int count) {
        this->x = x;
        this->y = y;
        this->hasBroken = hasBroken;
        this->count = count;
    }
};

const int WALL = 1;
const int BREAKABLE = 0; // 벽 하나를 부술 수 있는 상태
const int HAS_BROKEN = 1; // 이미 벽 하나를 부순 상태

const vector<pair<int, int>> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int N, M;
vector<vector<int>> maps(1001, vector<int>(1001));
vector<vector<vector<bool>>> visited(2, vector<vector<bool>>(1001, vector<bool>(1001, false)));

int main() {
    cin >> N >> M;

    // 지도 저장
    for (int i = 1; i <= N; i++) {
        string line;
        cin >> line;

        for (int j = 1; j <= M; j++) {
            maps[i][j] = line[j - 1] - '0';
        }
    }

    queue<Node> Q;

    Q.push(Node(1, 1, false, 1));
    visited[BREAKABLE][1][1] = true;

    int answer = -1;

    while (!Q.empty()) {
        auto [x, y, hasBroken, count] = Q.front(); Q.pop();

        // 종료 지점에 도착한 경우 최단 경로 반환
        if (x == N && y == M) {
            answer = count;
            break;
        }

        // 상하좌우로 인접한 칸 이동
        for (const auto& [dx, dy] : dr) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx < 1 || nx > N || ny < 1 || ny > M) continue;

            if (maps[nx][ny] == WALL) { // 다음 칸이 벽인 경우 -> 부숴야만 해당 칸 방문 가능
                if (!hasBroken && !visited[HAS_BROKEN][nx][ny]) { // 벽을 부술 수 있어서 부순 경우
                    Q.push(Node(nx, ny, true, count + 1));
                    visited[HAS_BROKEN][nx][ny] = true;
                }
            } else { // 다음 칸이 빈칸인 경우 -> 부수지 않아도 해당 칸 방문 가능
                if (!hasBroken && !visited[BREAKABLE][nx][ny]) { // 벽을 부술 수 있지만 부수지 않은 경우
                    Q.push(Node(nx, ny, false, count + 1));
                    visited[BREAKABLE][nx][ny] = true;
                }

                if (hasBroken && !visited[HAS_BROKEN][nx][ny]) { // 벽을 부술 수 없어서 부수지 않은 경우
                    Q.push(Node(nx, ny, true, count + 1));
                    visited[HAS_BROKEN][nx][ny] = true;
                }
            }
        }
    }

    cout << answer;
    
    return 0;
}