#define Coord pair<int, int>
#define X first
#define Y second

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 100;

int N, M;
int answer = 0; // 불을 켤 수 있는 방의 최대 개수
Coord start = make_pair(1, 1);

vector<Coord> switches[MAX + 1][MAX + 1]; // 각 방에 존재하는 스위치
bool visited[MAX + 1][MAX + 1]; // 방문 여부
bool lighted[MAX + 1][MAX + 1]; // 불 켜짐 여부

const vector<Coord> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
    cin >> N >> M;

    int x, y, a, b;

    // 스위치 저장
    for (int i = 0; i < M; i++) {
        cin >> x >> y >> a >> b;

        // (x, y) 방에서 (a, b) 방의 불을 켜고 끌 수 있음
        switches[x][y].push_back(make_pair(a, b));
    }

    queue<Coord> Q;

    Q.push(start);
    visited[start.X][start.Y] = true;
    lighted[start.X][start.Y] = true;
    answer++;

    // 너비 우선 탐색 수행
    while (!Q.empty()) {
        auto [x, y] = Q.front(); Q.pop();

        // 현재 위치한 (x, y) 방에 있는 모든 스위치 켜기
        for (const auto& [sx, sy] : switches[x][y]) {
            if (lighted[sx][sy]) continue;
            
            lighted[sx][sy] = true;
            answer++;

            // 새로 불이 켜진 방과 상하좌우로 인접한 방 확인
            for (const auto& [dx, dy] : dr) {
                int nsx = sx + dx;
                int nsy = sy + dy;

                if (nsx <= 0 || nsx > N || nsy <= 0 || nsy > N) continue;
                
                // 인접한 방에 방문한 적이 있다면 새로 불이 켜진 방에 도달할 수 있다는 의미
                if (visited[nsx][nsy]) {
                    Q.push(make_pair(sx, sy));
                    visited[sx][sy] = true;
                    break;
                }
            }
        }

        // 현재 위치한 (x, y) 방과 상하좌우로 인접한 방 확인
        for (const auto& [dx, dy] : dr) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
            if (visited[nx][ny] || !lighted[nx][ny]) continue;

            // 불이 켜져 있지만 아직 방문한 적이 없는 방 방문
            Q.push(make_pair(nx, ny));
            visited[nx][ny] = true;
        }
    }

    // 정답 출력
    cout << answer;
    
    return 0;
}