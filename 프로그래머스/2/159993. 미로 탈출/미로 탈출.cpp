#define Coord pair<int, int> // 좌표
#define X first
#define Y second

#include <string>
#include <vector>
#include <queue>

using namespace std;

const char START = 'S';
const char EXIT = 'E';
const char LEVER = 'L';
const char PATH = 'O';
const char WALL = 'X';

const int INF = -1;

const vector<Coord> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

Coord start;
Coord exits;
Coord lever;

int move(const Coord&, const Coord&, const vector<string>&, int, int);

int solution(vector<string> maps) {
    int row = (int)maps.size();
    int col = (int)maps[0].size();
    
    // 미로를 순회하며 특수 좌표 저장
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (maps[i][j] == START) { // 시작 지점
                start = make_pair(i, j);
            } else if (maps[i][j] == EXIT) { // 출구
                exits = make_pair(i, j);
            } else if (maps[i][j] == LEVER) { // 레버
                lever = make_pair(i, j);
            }
        }
    }
    
    // 시작 지점 -> 레버의 최소 이동 시간 계산
    int firstBfsResult = move(start, lever, maps, row, col);
        
    if (firstBfsResult == INF) {
        return INF;
    }
    
    // 레버 -> 출구의 최소 이동 시간 계산
    int secondBfsResult = move(lever, exits, maps, row, col);
        
    if (secondBfsResult == INF) {
        return INF;
    }
    
    return firstBfsResult + secondBfsResult;
}

int move(const Coord& src, const Coord& dest, const vector<string>& maps, int row, int col) {
    queue<Coord> q;
    int times[row][col];
    
    for (auto& row : times) {
        fill(row, row + col, INF);
    }
    
    q.push(src);
    times[src.X][src.Y] = 0;
    
    while (!q.empty()) {
        Coord curr = q.front(); q.pop();
        
        // 목적지에 도착한 경우 이동 시간 반환
        if (curr == dest) {
            return times[curr.X][curr.Y];
        }
        
        // 상하좌우 이동
        for (const auto& [dx, dy] : dr) {
            int nx = curr.X + dx;
            int ny = curr.Y + dy;
            
            if (nx < 0 || nx >= row || ny < 0 || ny >= col) continue;
            if (times[nx][ny] != INF) continue;
            if (maps[nx][ny] == WALL) continue;
            
            q.push(make_pair(nx, ny));
            times[nx][ny] = times[curr.X][curr.Y] + 1;
        }
    }
    
    // 목적지에 도착할 수 없는 경우 INF(-1) 반환
    return INF;
}