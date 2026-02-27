#define Coord pair<int, int>
#define X first
#define Y second
#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x;
    int y;
    int remainingSkillCount; // 사용 가능한 능력 횟수
    int moveCount;

    Node(int x, int y, int remainingSkillCount, int moveCount) {
        this->x = x;
        this->y = y;
        this->remainingSkillCount = remainingSkillCount;
        this->moveCount = moveCount;
    }
};

const int OBSTACLE = 1; // 장애물

const vector<Coord> horseMoves = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
const vector<Coord> monkeyMoves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int K, W, H;

// 프로토타입
bool isOutOfRange(int, int);

int main() {
    cin >> K;
    cin >> W >> H;

    vector<vector<int>> grid(H, vector<int>(W));

    // 격자판 정보 저장
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }

    // 출발지, 도착지 정의
    Coord source = make_pair(0, 0);
    Coord destination = make_pair(H - 1, W - 1);

    queue<Node> Q;
    vector<vector<vector<bool>>> visited(K + 1, vector<vector<bool>>(H, vector<bool>(W, false)));

    Q.push(Node(source.X, source.Y, K, 0));
    visited[K][source.X][source.Y] = true;

    int answer = -1;

    // 너비 우선 탐색 기반 최소 이동 횟수 계산
    while (!Q.empty()) {
        Node curr = Q.front(); Q.pop();

        // 도착지에 다다른 경우 이동 횟수 반환 후 탐색 종료
        if (curr.x == destination.X && curr.y == destination.Y) {
            answer = curr.moveCount;
            break;
        }

        // 능력을 사용해서 평지로 이동하는 경우
        if (curr.remainingSkillCount >= 1) {
            for (const auto& [dx, dy] : horseMoves) {
                int nx = curr.x + dx;
                int ny = curr.y + dy;

                if (isOutOfRange(nx, ny) || grid[nx][ny] == OBSTACLE) {
                    continue;
                }

                if (visited[curr.remainingSkillCount - 1][nx][ny]) {
                    continue;
                }

                Q.push(Node(nx, ny, curr.remainingSkillCount - 1, curr.moveCount + 1));
                visited[curr.remainingSkillCount - 1][nx][ny] = true;        
            }
        }

        // 능력을 사용하지 않고 평지로 이동하는 경우
        for (const auto& [dx, dy] : monkeyMoves) {
            int nx = curr.x + dx;
            int ny = curr.y + dy;

            if (isOutOfRange(nx, ny) || grid[nx][ny] == OBSTACLE) {
                continue;
            }

            if (visited[curr.remainingSkillCount][nx][ny]) {
                continue;
            }

            Q.push(Node(nx, ny, curr.remainingSkillCount, curr.moveCount + 1));
            visited[curr.remainingSkillCount][nx][ny] = true;   
        }
    }

    cout << answer;
    
    return 0;
}

bool isOutOfRange(int x, int y) {
    return x < 0 || x >= H || y < 0 || y >= W;
}