#define Coord pair<int, int>
#define X first
#define Y second

#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int NONE = -1;
const int MAX = 100;
const char SEA = 'X';

queue<Coord> q;
vector<vector<bool>> visited(MAX, vector<bool>(MAX, false));

const vector<Coord> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int bfs(const Coord& start, const vector<string>& maps, int row, int col);
int getNumber(char ch);

vector<int> solution(vector<string> maps) {
    vector<int> answer;
    
    int row = (int)maps.size();
    int col = (int)maps[0].size();
    
    // 무인도 방문
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!visited[i][j] && maps[i][j] != SEA) {
                int total = bfs(make_pair(i, j), maps, row, col);
                
                if (total > 0) {
                    answer.push_back(total);
                }
            }
        }
    }
    
    if (answer.empty()) {
        answer.push_back(NONE);
    }
    
    // 오름차순 정렬
    sort(answer.begin(), answer.end());
    
    return answer;
}

int bfs(const Coord& start, const vector<string>& maps, int row, int col) {
    int total = 0;
    
    q.push(start);
    visited[start.X][start.Y] = true;
    total += getNumber(maps[start.X][start.Y]);
    
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        
        // 상하좌우 이동
        for (const auto& [dx, dy] : dr) {
            int nx = x + dx;
            int ny = y + dy;
            
            if (nx < 0 || nx >= row || ny < 0 || ny >= col) continue;
            if (visited[nx][ny] || maps[nx][ny] == SEA) continue;
            
            q.push(make_pair(nx, ny));
            visited[nx][ny] = true;
            total += getNumber(maps[nx][ny]);
        }
    }
    
    return total;
}

// char -> int 변환
int getNumber(char ch) {
    return ch - '0';
}