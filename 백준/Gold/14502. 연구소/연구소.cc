#define Coord pair<int, int>
#define X first
#define Y second
#include <bits/stdc++.h>

using namespace std;

int N, M;

vector<Coord> initSpaces;
vector<Coord> initViruses;

queue<Coord> Q;

const int NEW_WALL_COUNT = 3;

const int SPACE = 0;
const int WALL = 1;
const int VIRUS = 2;

const vector<Coord> dr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 프로토타입
bool isOutOfRange(int x, int y);
int spread(const vector<vector<int>>& maps);

int main() {
    // 빠른 입출력 설정
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    vector<vector<int>> maps(N, vector<int>(M));

    int initWallCount = 0;

    // 연구소 지도 저장
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> maps[i][j];
            
            if (maps[i][j] == SPACE) {
                initSpaces.push_back(Coord(i, j));
            } else if (maps[i][j] == VIRUS) {
                initViruses.push_back(Coord(i, j));
            } else if (maps[i][j] == WALL) {
                initWallCount++;
            }
        }
    }

    int answer = 0;
    int initSpaceCount = (int)initSpaces.size();
    int initVirusCount = (int)initViruses.size();
    
    for (int i = 0; i < initSpaceCount - 2; i++) {
        Coord first = initSpaces[i];
        
        for (int j = i + 1; j < initSpaceCount - 1; j++) {
            Coord second = initSpaces[j];
            
            for (int k = j + 1; k < initSpaceCount; k++) {
                Coord third = initSpaces[k];
                
                // 벽 세우기
                maps[first.X][first.Y] = WALL;
                maps[second.X][second.Y] = WALL;
                maps[third.X][third.Y] = WALL;

                // 바이러스 확산 후 안전 영역의 크기 계산
                int spreadCount = spread(maps);
                int safeAreaSize = N * M - initWallCount - NEW_WALL_COUNT - initVirusCount - spreadCount;

                // 안전 영역의 최대 크기 갱신
                answer = max(answer, safeAreaSize);

                // 벽 허물기
                maps[first.X][first.Y] = SPACE;
                maps[second.X][second.Y] = SPACE;
                maps[third.X][third.Y] = SPACE;
            }
        }
    }

    cout << answer;
    
    return 0;
}

bool isOutOfRange(int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= M;
}

int spread(const vector<vector<int>>& maps) {
    int spreadCount = 0;
    vector<vector<int>> temp = maps;
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    for (const Coord& virus : initViruses) {
        Q.push(virus);
        visited[virus.X][virus.Y] = true;
    }

    while (!Q.empty()) {
        auto [x, y] = Q.front(); Q.pop();

        for (const auto& [dx, dy] : dr) {
            int nx = x + dx;
            int ny = y + dy;

            if (isOutOfRange(nx, ny) || visited[nx][ny]) {
                continue;
            }

            if (temp[nx][ny] != SPACE) {
                continue;
            }

            Q.push(Coord(nx, ny));
            temp[nx][ny] = VIRUS;
            visited[nx][ny] = true;
            spreadCount++;
        }
    }

    return spreadCount;
}