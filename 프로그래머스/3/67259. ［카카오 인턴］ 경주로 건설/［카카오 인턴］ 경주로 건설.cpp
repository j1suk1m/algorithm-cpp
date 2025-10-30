#define Coord pair<int, int>
#define X first
#define Y second

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

enum Direction {
    INIT = -1,
    UP = 0, 
    LEFT = 1, 
    RIGHT = 2, 
    DOWN = 3
};

struct Node {
    int x;
    int y;
    int cost;
    Direction dir;
    
    Node(int x, int y, int cost, Direction dir) {
        this->x = x;
        this->y = y;
        this->cost = cost;
        this->dir = dir;
    }
};

const int WALL = 1;
const int INF = 25 * 25 * 600; 
const vector<Coord> dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

// 프로토타입
bool isOutOfRange(int N, int x, int y);
bool isStraight(Direction d1, Direction d2);
int getExtraCost(Direction d1, Direction d2);
Direction toDirection(int value);

int solution(vector<vector<int>> board) {
    int N = (int)board.size();
    vector<vector<vector<int>>> costs(N, vector<vector<int>>(N, vector<int>(4, INF)));
    queue<Node> Q;
    Coord start = make_pair(0, 0);
    
    Q.push(Node(start.X, start.Y, 0, INIT));
    
    for (int i = 0; i < 4; i++) {
        costs[start.X][start.Y][i] = 0;
    }
    
    // 너비 우선 탐색
    while (!Q.empty()) {
        auto [x, y, cost, dir] = Q.front(); Q.pop();
        
        // 상하좌우 탐색
        for (int i = 0; i < 4; i++) {
            int nx = x + dirs[i].X;
            int ny = y + dirs[i].Y;
            
            if (isOutOfRange(N, nx, ny) || board[nx][ny] == WALL) continue;
            
            Direction nDir = toDirection(i);
            int nCost = cost + getExtraCost(dir, nDir);
            
            // 최소 비용을 갱신할 수 있는 경우
            if (costs[nx][ny][i] > nCost) {
                Q.push(Node(nx, ny, nCost, nDir));
                costs[nx][ny][i] = nCost;
            }
        }
    }
    
    int answer = INF;
    
    // 네 방향 중 최소 비용 찾기
    for (int i = 0; i < 4; i++) {
        answer = min(answer, costs[N - 1][N - 1][i]);
    }
    
    return answer;
}

bool isOutOfRange(int N, int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= N;
}

bool isStraight(Direction d1, Direction d2) {
    return d1 == INIT || d2 == INIT || d1 == d2;
}

int getExtraCost(Direction d1, Direction d2) {
    return isStraight(d1, d2) ? 100 : 600;
}

Direction toDirection(int value) {
    return static_cast<Direction>(value);
}