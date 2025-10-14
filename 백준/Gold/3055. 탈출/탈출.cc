#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

// 맵 문자
const char EMPTY = '.';
const char WATER = '*';
const char STONE = 'X';
const char CAVE = 'D';
const char HEDGEHOG = 'S';

// 좌표 이동
const vector<int> dx = {-1, 1, 0, 0};
const vector<int> dy = {0, 0, -1, 1};

// 맵 크기
int R, C;

// 맵과 좌표
vector<vector<char>> map;
pair<int, int> cave;
pair<int, int> hedgehog;

// BFS용 2차원 벡터
vector<pair<int, int>> waters;
vector<vector<int>> waterTime;

// 최소 도착 시간
int answer;

// 범용 템플릿 함수 // 2차원 벡터 v를 R * C 크기로 재조정
template <typename T> 
void resize2DVector(vector<vector<T>> &v, const T &init = T()) {
    v.resize(R);

    for (int i = 0; i < R; i++) {
        v[i].resize(C, init);
    }
}

// 프로토타입
void initMap();
bool isOutOfRange(int x, int y);
void flow();
bool canArriveAtCave();

int main() {
    cin >> R >> C;

    // 지도 초기화 후 저장
    resize2DVector(map);
    initMap();

    // 물 이동
    resize2DVector(waterTime);
    flow();

    // 고슴도치 이동 후 결과 출력
    if (canArriveAtCave()) {
        cout << answer;
    } else {
        cout << "KAKTUS";
    }

    return 0;
}

// 지도 저장
void initMap() {
    string row;
    
    for (int i = 0; i < R; i++) {
        cin >> row;

        for (int j = 0; j < C; j++) {
            char curr = row[j];
            map[i][j] = curr;

            // 특수 좌표 저장
            if (curr == CAVE) cave = {i, j};
            else if (curr == HEDGEHOG) hedgehog = {i, j};
            else if (curr == WATER) waters.push_back({i, j});
        }
    }    
}

bool isOutOfRange(int x, int y) {
    return x < 0 || x >= R || y < 0 || y >= C;
}

// 물의 최소 이동 시간 저장
void flow() {
    queue<pair<int, int>> q;

    for (const pair<int, int>& p : waters) {
        q.push(p);
        waterTime[p.first][p.second] = 1;
    }

    int time;

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        time = waterTime[x][y];

        // 상하좌우 이동
        for (int i = 0; i < dx.size(); i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isOutOfRange(nx, ny)) continue;
            if (map[nx][ny] == STONE || map[nx][ny] == CAVE) continue;
            
            if (waterTime[nx][ny] == 0 || waterTime[nx][ny] > time + 1) {
                q.push({nx, ny});
                waterTime[nx][ny] = time + 1;
            }
        }
    }
}

// 고슴도치의 도착 가능 여부 반환
bool canArriveAtCave() {
    queue<tuple<int, int, int>> q;
    vector<vector<bool>> visited(R, vector<bool>(C, false));

    auto [x, y] = hedgehog;
    q.push(make_tuple(x, y, 1));
    visited[x][y] = true;

    while (!q.empty()) {
        auto [x, y, time] = q.front(); q.pop();

        // 종료 지점에 도착한 경우
        if (x == cave.first && y == cave.second) {
            answer = time - 1; // 1분부터 시작했으므로 1을 빼줌
            return true;
        }

        // 상하좌우 이동
        for (int i = 0; i < dx.size(); i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isOutOfRange(nx, ny) || visited[nx][ny]) continue;
            if (map[nx][ny] == STONE) continue;
            if (waterTime[nx][ny] != 0 && waterTime[nx][ny] <= time + 1) continue;

            q.push(make_tuple(nx, ny, time + 1));
            visited[nx][ny] = true;
        }
    }

    return false;
}