#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Time {
    DAY, NIGHT
};

struct Node {
    int x;
    int y;
    int breakCount; // 지금까지 벽을 부순 횟수
    int dist;
    Time time;

    Node(int x, int y, int breakCount, int dist, Time time) {
        this->x = x;
        this->y = y;
        this->breakCount = breakCount;
        this->dist = dist;
        this->time = time;
    }
};

const int WALL = 1;

const vector<pair<int, int>> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int N, M, K;
vector<vector<int>> maps(1001, vector<int>(1001));
vector<vector<vector<vector<bool>>>> visited(2, vector<vector<vector<bool>>>(11, vector<vector<bool>>(1001, vector<bool>(1001, false))));

Time getNextTime(Time curr);

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

    Q.push(Node(1, 1, 0, 1, DAY));
    visited[DAY][0][1][1] = true; // 낮에 벽을 0번 부순 상태로 (1, 1) 방문

    int answer = -1;

    while (!Q.empty()) {
        auto [x, y, breakCount, dist, time] = Q.front(); Q.pop();

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
                if (time == DAY && breakCount < K && !visited[NIGHT][breakCount + 1][nx][ny]) { // 벽 부수고 다음 칸 방문
                    Q.push(Node(nx, ny, breakCount + 1, dist + 1, NIGHT));
                    visited[NIGHT][breakCount + 1][nx][ny] = true;
                } else if (time == NIGHT && !visited[DAY][breakCount][x][y]) { // 낮이 될 때까지 제자리에서 대기
                    Q.push(Node(x, y, breakCount, dist + 1, DAY));
                    visited[DAY][breakCount][x][y] = true;
                }
            } else { // 다음 칸이 빈칸인 경우 -> 부수지 않아도 해당 칸 방문 가능
                Time nextTime = getNextTime(time);
                
                if (!visited[nextTime][breakCount][nx][ny]) { // 즉시 다음 칸 방문
                    Q.push(Node(nx, ny, breakCount, dist + 1, nextTime));
                    visited[nextTime][breakCount][nx][ny] = true;                    
                }
            }
        }
    }

    cout << answer;
    
    return 0;
}

Time getNextTime(Time curr) {
    return curr == DAY ? NIGHT : DAY;
}