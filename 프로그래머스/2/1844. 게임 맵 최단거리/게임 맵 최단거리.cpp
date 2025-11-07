#define Coord pair<int, int>
#define X first
#define Y second

#include <vector>
#include <queue>

using namespace std;

const int WALL = 0;
const vector<Coord> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int solution(vector<vector<int>> maps) {
    int N = (int)maps.size();
    int M = (int)maps[0].size();
    
    Coord start = make_pair(0, 0);
    Coord end = make_pair(N - 1, M - 1);
    
    queue<Coord> Q;
    vector<vector<int>> count(N, vector<int>(M));
 
    Q.push(start);
    count[start.X][start.Y] = 1;
    
    // 너비 우선 탐색 실행
    while (!Q.empty()) {
        auto [x, y] = Q.front(); Q.pop();
        
        // 상대 팀 진영에 도착한 경우 최단 거리 반환
        if (x == end.X && y == end.Y) {
            return count[x][y];
        }
        
        // 상하좌우로 인접한 칸 방문
        for (const auto& [dx, dy] : dr) {
            int nx = x + dx;
            int ny = y + dy;
            
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if (maps[nx][ny] == WALL || count[nx][ny] > 0) continue;
            
            Q.push(make_pair(nx, ny));
            count[nx][ny] = count[x][y] + 1;
        }
    }
    
    return -1;
}