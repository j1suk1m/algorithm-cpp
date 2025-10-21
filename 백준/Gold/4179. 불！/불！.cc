#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int R, C; // 행, 열
int answer;
vector<vector<char>> maze;
vector<vector<int>> fireTime; // 각 칸에 불이 처음으로 번지는 시간
vector<pair<int, int>> fires; // 초기 불 위치
pair<int, int> person; // 초기 사람 위치

const char WALL = '#';
const char SPACE = '.';
const char PERSON = 'J';
const char FIRE = 'F';

const string IMPOSSIBLE = "IMPOSSIBLE";
const int INF = -1; // 미로 탈출 불가 시 반환하는 값
const vector<pair<int, int>> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 프로토타입
bool isOutOfRange(int x, int y);
bool canEscape(int x, int y);
void spreadFire();
int escape();

int main() {
    cin >> R >> C;

    maze.resize(R);
    fireTime.resize(R);

    for (int i = 0; i < R; i++) {
        maze[i].resize(C, 0);
        fireTime[i].resize(C, INF);
    }
    
    string row;

    // 미로 저장
    for (int i = 0; i < R; i++) {
        cin >> row;

        for (int j = 0; j < row.size(); j++) {
            maze[i][j] = row[j];

            // 특수 좌표 저장
            if (maze[i][j] == FIRE) fires.push_back(make_pair(i, j));
            if (maze[i][j] == PERSON) person = make_pair(i, j);
        }
    }

    spreadFire();
    int time = escape();

    cout << (time == INF ? IMPOSSIBLE : to_string(time));
}

bool isOutOfRange(int x, int y) {
    return x < 0 || x >= R || y < 0 || y >= C;
}

bool canEscape(int x, int y) {
    return x == 0 || x == R - 1 || y == 0 || y == C - 1;
}

void spreadFire() {
    queue<pair<int, int>> q;

    for (const pair<int, int>& fire : fires) {
        q.push(fire);
        fireTime[fire.first][fire.second] = 1;
    }

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        for (const auto& [dx, dy] : dr) {
            int nx = x + dx;
            int ny = y + dy;

            if (isOutOfRange(nx, ny)) continue;
            if (maze[nx][ny] == WALL) continue;
            if (fireTime[nx][ny] != INF) continue;

            q.push(make_pair(nx, ny));
            fireTime[nx][ny] = fireTime[x][y] + 1;
        }
    }
}

int escape() {
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    vector<vector<int>> time(R, vector<int>(C, 0));

    q.push(person);
    visited[person.first][person.second] = true;
    time[person.first][person.second] = 1;

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        if (canEscape(x, y)) return time[x][y];

        int nextTime = time[x][y] + 1;

        for (const auto& [dx, dy] : dr) {
            int nx = x + dx;
            int ny = y + dy;

            if (isOutOfRange(nx, ny)) continue;
            if (maze[nx][ny] == WALL) continue;
            if (visited[nx][ny]) continue;
            if (fireTime[nx][ny] != INF && nextTime >= fireTime[nx][ny]) continue;

            q.push(make_pair(nx, ny));
            visited[nx][ny] = true;
            time[nx][ny] = nextTime;
        }        
    }

    return INF;
}