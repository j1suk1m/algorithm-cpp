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
    int time;
    bool isFire;

    Node(int x, int y, int time, bool isFire) {
        this->x = x;
        this->y = y;
        this->time = time;
        this->isFire = isFire;
    }
};

const char EMPTY = '.';
const char WALL = '#';
const char START = '@';
const char FIRE = '*';

// 상하좌우 이동
const vector<Coord> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
    int testCaseCount, width, height;

    cin >> testCaseCount;

    // [0] 테스트 케이스 실행
    while (testCaseCount-- > 0) {
        cin >> width >> height;

        vector<vector<char>> building(height, vector<char>(width));
        vector<Coord> fires;
        Coord start;
        string line;

        // [1] 빌딩 지도 저장
        for (int i = 0; i < height; i++) {
            cin >> line;

            for (int j = 0; j < width; j++) {
                building[i][j] = line[j];

                // 특수 좌표 저장
                if (line[j] == START) { // 시작 위치
                    start = make_pair(i, j);
                } else if (line[j] == FIRE) { // 불 위치
                    fires.push_back(make_pair(i, j));
                }
            }
        }

        queue<Node> Q;
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        string answer = "IMPOSSIBLE";

        // 불이 먼저 이동하도록 큐에 미리 추가
        for (const auto& [x, y] : fires) {
            Q.push(Node(x, y, 0, true));
        }

        Q.push(Node(start.X, start.Y, 0, false));
        visited[start.X][start.Y] = true;

        // [2] 너비 우선 탐색 실행
        while (!Q.empty()) {
            auto [x, y, time, isFire] = Q.front(); Q.pop();

            // 빌딩을 탈출할 수 있는 경우 최소 시간 저장 후 탐색 종료
            if (!isFire && (x == 0 || x == height - 1 || y == 0 || y == width - 1)) {
                answer = to_string(time + 1); // 현재 빌딩 가장자리에 있으므로 다음 시간에 탈출
                break;
            }

            // 상하좌우 이동
            for (const auto& [dx, dy] : dr) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx < 0 || nx >= height || ny < 0 || ny >= width) continue;
                if (building[nx][ny] == FIRE || building[nx][ny] == WALL) continue;
                
                if (isFire) {
                    Q.push(Node(nx, ny, time + 1, true));
                    building[nx][ny] = FIRE;
                } else {
                    if (!visited[nx][ny]) {
                        Q.push(Node(nx, ny, time + 1, false));
                        visited[nx][ny] = true;
                    }
                }
            }
        }
        
        cout << answer << "\n";
    }
    
    return 0;
}