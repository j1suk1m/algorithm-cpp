#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char SEA = 'X';
const int NONE = -1;
const vector<pair<int, int>> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int dfs(int x, int y, int row, int col, const vector<string>& maps, vector<vector<bool>>& visited);
    
vector<int> solution(vector<string> maps) {
    int row = (int)maps.size();
    int col = (int)maps[0].size();
    vector<int> answer;
    vector<vector<bool>> visited(row, vector<bool>(col, false));
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (maps[i][j] != SEA && !visited[i][j]) {
                int result = dfs(i, j, row, col, maps, visited);
                answer.push_back(result);
            }
        }
    }
    
    if (answer.empty()) {
        answer.push_back(NONE);
    } else {
        sort(answer.begin(), answer.end());       
    }
  
    return answer;
}

int dfs(int x, int y, int row, int col, const vector<string>& maps, vector<vector<bool>>& visited) {
    int result = maps[x][y] - '0';
    visited[x][y] = true;
    
    for (const auto& [dx, dy] : dr) {
        int nx = x + dx;
        int ny = y + dy;
        
        if (nx < 0 || nx >= row || ny < 0 || ny >= col) continue;
        if (maps[nx][ny] == SEA || visited[nx][ny]) continue;
        
        result += dfs(nx, ny, row, col, maps, visited);
    }
    
    return result;
}