#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int answer;
int N, M;
int initialSafetyArea;

vector<vector<int>> lab;
vector<pair<int, int>> emptySpaces;
vector<pair<int, int>> viruses;

const int BUILD_COUNT = 3;

// 연구소 좌표 값
const int EMPTY_SPACE = 0;
const int WALL = 1;
const int VIRUS = 2;

// 상하좌우 이동
const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 프로토타입
bool isOutOfRange(int x, int y);
int spreadViruses(vector<vector<int>> lab);
void buildWalls(int buildCount, int index);

int main() {
    cin >> N >> M;

    // 연구소 크기 재조정
    lab.resize(N);

    for (int i = 0; i < N; i++) {
        lab[i].resize(M);
    }

    // 연구소 지도 저장
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> lab[i][j];

            if (lab[i][j] == EMPTY_SPACE) {
                emptySpaces.push_back(make_pair(i, j));
                initialSafetyArea++;
            } else if (lab[i][j] == VIRUS) {
                viruses.push_back(make_pair(i, j));
            }
        }
    }

    buildWalls(0, 0);

    cout << answer;
    
    return 0;
}

bool isOutOfRange(int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= M;
}

// 너비 우선 탐색으로 바이러스 확산
int spreadViruses(vector<vector<int>> lab) {
    queue<pair<int, int>> q;
    int safetyArea = initialSafetyArea - BUILD_COUNT;

    // 초기 바이러스 좌표 큐에 저장
    for (const auto& p : viruses) {
        q.push(p);
    }

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (isOutOfRange(nx, ny)) continue;
            if (lab[nx][ny] != EMPTY_SPACE) continue;

            q.push(make_pair(nx, ny));
            lab[nx][ny] = VIRUS;
            safetyArea--;
        }
    }

    return safetyArea;
}

// 벽을 세우고 바이러스를 확산시킨 뒤 안전 영역의 최대 개수 갱신
void buildWalls(int buildCount, int index) {
    if (buildCount == BUILD_COUNT) {
        int safetyArea = spreadViruses(lab);
        answer = max(answer, safetyArea);
        return;
    }

    for (int i = index; i < emptySpaces.size(); i++) {
        auto [x, y] = emptySpaces[i];
        lab[x][y] = WALL;
        buildWalls(buildCount + 1, i + 1);
        lab[x][y] = EMPTY_SPACE;
    }
}