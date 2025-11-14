#define Coord pair<int, int>
#define X first
#define Y second

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int x;
    int y;
    int moveCount; // 이동 횟수
    int useCount; // 말 능력 사용 횟수

    Node(int x, int y, int moveCount, int useCount) {
        this->x = x;
        this->y = y;
        this->moveCount = moveCount;
        this->useCount = useCount;
    }
};

const int OBSTACLE = 1;
const vector<Coord> horseMoves = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
const vector<Coord> monkeyMoves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
    int K, W, H;

    cin >> K;
    cin >> W >> H;

    vector<vector<int>> grid(H, vector<int>(W));

    // 격자 저장
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }

    queue<Node> Q;
    vector<vector<vector<bool>>> visited(K + 1, vector<vector<bool>>(H, vector<bool>(W, false))); // (K + 1) * H * W 크기 방문 여부 배열
    Coord start = make_pair(0, 0); // 출발 지점
    Coord end = make_pair(H - 1, W - 1); // 도착 지점

    Q.push(Node(start.X, start.Y, 0, 0));
    visited[0][start.X][start.Y] = true; // 능력을 0번 사용한 상태로 (start.X, start.Y) 방문

    int answer = -1;

    // 너비 우선 탐색 수행
    while (!Q.empty()) {
        auto [x, y, moveCount, useCount] = Q.front(); Q.pop();

        // 도착 지점에 도달한 경우 최소 이동 횟수 저장 후 탐색 종료
        if (x == end.X && y == end.Y) {
            answer = moveCount;
            break;
        }

        // 말 능력을 사용하는 경우
        if (useCount < K) {
            for (const auto& [dx, dy] : horseMoves) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
                if (visited[useCount + 1][nx][ny]) continue;
                if (grid[nx][ny] == OBSTACLE) continue;

                Q.push(Node(nx, ny, moveCount + 1, useCount + 1));
                visited[useCount + 1][nx][ny] = true; // 능력을 한 번 더 사용한 상태로 (nx, ny) 방문
            }
        }

        // 말 능력을 사용하지 않는 경우
        for (const auto& [dx, dy] : monkeyMoves) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (visited[useCount][nx][ny]) continue;
            if (grid[nx][ny] == OBSTACLE) continue;

            Q.push(Node(nx, ny, moveCount + 1, useCount));
            visited[useCount][nx][ny] = true; // 능력을 사용하지 않은 상태로 (nx, ny) 방문
        }
    }

    cout << answer;
    
    return 0;
}