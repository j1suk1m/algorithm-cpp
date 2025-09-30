#include<vector>
#include<queue>
#include<array>

using namespace std;

int n;
int m;
const int WALL = 0;
const array<int, 4> dx = {-1, 1, 0, 0};
const array<int, 4> dy = {0, 0, -1, 1};

struct Node {
    int x;
    int y;
    
    Node(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

bool isArrived(int x, int y) {
    return x == n - 1 && y == m - 1;
}

bool isOutOfRange(int x, int y) {
    return x < 0 || x >= n || y < 0 || y >= m;
}

int bfs(vector<vector<int>>& maps, int x, int y) {
    queue<Node> queue;
    queue.push(Node(x, y));
    
    while(!queue.empty()) {
        Node curr = queue.front();
        queue.pop();
        
        // 상대 팀 진영에 도착
        if (isArrived(curr.x, curr.y)) {
            return maps[curr.x][curr.y];
        }
        
        // 상하좌우 탐색
        for (int i = 0; i < dx.size(); i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            
            if (isOutOfRange(nx, ny)) continue;
            if (maps[nx][ny] == WALL || maps[nx][ny] > 1) continue;
            
            queue.push(Node(nx, ny));
            maps[nx][ny] = maps[curr.x][curr.y] + 1;
        }
    }
    
    return -1;
}

int solution(vector<vector<int>> maps) {
    n = maps.size();
    m = maps[0].size();
    
    return bfs(maps, 0, 0);
}