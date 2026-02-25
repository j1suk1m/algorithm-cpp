#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x;
    int y;
    bool skillUsed; // (x, y)에 도착할 때까지 벽을 부순 적이 있는지
    int count;

    Node(int x, int y, bool skillUsed, int count) {
        this->x = x;
        this->y = y;
        this->skillUsed = skillUsed;
        this->count = count;
    }
};

const int WALL = 1;
const int SKILL_NOT_USED = 0; // 벽 하나를 부술 수 있는 상태
const int SKILL_USED = 1; // 이미 벽 하나를 부숴서 더이상 부술 수 없는 상태

const vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> maps(N + 1, vector<int>(M + 1));

    // 맵 정보 저장
    for (int i = 1; i <= N; i++) {
        string row;
        cin >> row;

        for (int j = 1; j <= M; j++) {
            maps[i][j] = row[j - 1] - '0';
        }
    }

    // 출발지, 도착지 정의
    pair<int, int> source = make_pair(1, 1);
    pair<int, int> destination = make_pair(N, M);

    queue<Node> Q;
    vector<vector<vector<int>>> visited(2, vector<vector<int>>(N + 1, vector<int>(M + 1, false)));

    // 출발지 방문 처리
    Q.push(Node(source.first, source.second, false, 1));
    visited[SKILL_NOT_USED][source.first][source.second] = true;

    int answer = -1;

    while (!Q.empty()) {
        Node curr = Q.front(); Q.pop();

        // 목적지에 도착한 경우 탐색 종료
        if (curr.x == destination.first && curr.y == destination.second) {
            answer = curr.count;
            break;
        }

        // 상하좌우 이동
        for (const auto& [dx, dy] : dir) {
            int nx = curr.x + dx;
            int ny = curr.y + dy;

            if (nx < 1 || nx > N || ny < 1 || ny > M) {
                continue;
            }

            if (maps[nx][ny] == WALL) { // 인접한 칸이 벽인 경우
                if (!curr.skillUsed && !visited[SKILL_USED][nx][ny]) { // 부술 수 있다면 부수고 방문
                    Q.push(Node(nx, ny, true, curr.count + 1));
                    visited[SKILL_USED][nx][ny] = true;
                }
            } else { // 인접한 칸이 벽이 아닌 경우
                if (!curr.skillUsed && !visited[SKILL_NOT_USED][nx][ny]) { // 부술 수 있는데 부수지 않고 방문
                    Q.push(Node(nx, ny, false, curr.count + 1));
                    visited[SKILL_NOT_USED][nx][ny] = true;
                } else if (curr.skillUsed && !visited[SKILL_USED][nx][ny]) { // 부술 수 없어서 부수지 않고 방문
                    Q.push(Node(nx, ny, true, curr.count + 1));
                    visited[SKILL_USED][nx][ny] = true;
                }
            }
        }
    }

    cout << answer;
    
    return 0;
}