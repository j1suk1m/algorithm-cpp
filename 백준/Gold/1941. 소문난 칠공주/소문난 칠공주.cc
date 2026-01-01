#define X first
#define Y second
#define Coord pair<int, int>

#include <iostream> // cin, cout
#include <vector> // vector
#include <utility> // pair
#include <queue> // queue

using namespace std;

const int X = 5;
const int Y = 5;
const int TOTAL = 7;
const int S_MIN_COUNT = 4;
const vector<Coord> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 상하좌우 이동

int answer;
vector<vector<char>> classroom(X, vector<char>(Y));
vector<Coord> selectedSpots;

// 프로토타입
bool isOutOfRange(int, int);
bool isConnected();
void organize(int, int, int);

int main() {
    string input;

    // 자리 저장
    for (int x = 0; x < X; x++) {
        cin >> input;

        for (int y = 0; y < Y; y++) {
            classroom[x][y] = input[y];
        }
    }

    int start = 0;
    int sCount = 0;
    int yCount = 0;
    
    organize(start, sCount, yCount);

    cout << answer;
    
    return 0;
}

bool isOutOfRange(int x, int y) {
    return x < 0 || x >= X || y < 0 || y >= Y;
}

bool isConnected() {
    bool selected[X][Y] = {false, };
    bool visited[X][Y] = {false, };

    // 선택된 자리 표시
    for (const auto& [x, y] : selectedSpots) {
        selected[x][y] = true;
    }

    int count;
    queue<Coord> Q;
    Coord startSpot = selectedSpots[0];
    
    Q.push(startSpot);
    visited[startSpot.X][startSpot.Y] = true;
    count = 1;

    // 선택된 모든 자리가 상하좌우로 인접하도록 연결되어 있는지 확인
    while (!Q.empty()) {
        auto [x, y] = Q.front(); Q.pop();

        for (const auto& [dx, dy] : dr) {
            int nx = x + dx;
            int ny = y + dy;

            if (isOutOfRange(nx, ny)) continue;
            if (!selected[nx][ny]) continue;
            if (visited[nx][ny]) continue;

            Q.push(make_pair(nx, ny));
            visited[nx][ny] = true;
            count++;
        }
    }

    return count == TOTAL;
}

void organize(int start, int sCount, int yCount) {
    // 가지치기
    if (yCount > TOTAL - S_MIN_COUNT) {
        return;
    }

    if (sCount + yCount == TOTAL) {
        if (isConnected()) answer++;
        return;
    }

    for (int i = start; i < X * Y; i++) {
        int x = i / X;
        int y = i % Y;
        
        int nextSCount = sCount;
        int nextYCount = yCount;

        if (classroom[x][y] == 'S') nextSCount++;
        else if (classroom[x][y] == 'Y') nextYCount++;
            
        selectedSpots.push_back(make_pair(x, y));
        organize(i + 1, nextSCount, nextYCount);
        selectedSpots.pop_back();
    }
}