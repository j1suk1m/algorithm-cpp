#define Coord pair<int, int>

#include <iostream> // cin, cout
#include <vector> // vector
#include <algorithm> // max
#include <utility> // pair
#include <queue> // queue

using namespace std;

const int NOT_ARRIVED = -1;

// 정원 지도 값
const int LAKE = 0;
const int FERTILE_LAND = 2;

// 배양액 및 상태 값
const int GREEN = 3;
const int RED = 4;
const int FLOWER = 5;

// 상하좌우 이동
const vector<Coord> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int answer = 0;
int N, M, G, R;

vector<vector<int>> garden;
vector<Coord> fertilePoints; // 배양액을 배치할 수 있는 모든 위치
vector<Coord> selectedPoints; // 배양액을 배치하기 위해 현재 선택된 위치
vector<int> fertilizerType; // selectedPoints 각 위치에 배치된 배양액 종류

// 프로토타입
bool isOutOfRange(int x, int y);
void simulate();
void assignFertiles(int index, int greenCount);
void selectPositions(int start, int selectedCount);

int main() {
    cin >> N >> M >> G >> R;

    garden.assign(N, vector<int>(M));

    // 정원 지도 저장
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            int point;
            cin >> point;
            garden[x][y] = point;

            // 배양액을 배치할 수 있는 위치 저장
            if (point == FERTILE_LAND) {
                fertilePoints.push_back(make_pair(x, y));
            }
        }
    }

    selectPositions(0, 0);

    cout << answer;
    
    return 0;
}

// 좌표가 정원 범위를 벗어나는지 확인
bool isOutOfRange(int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= M;
}

// 선택된 배양액 배치에 대해 BFS 시뮬레이션 수행
void simulate() {
    int flowersCount = 0;

    // 각 칸에 배양액이 처음 도착한 시간
    vector<vector<int>> arriveTime(N, vector<int>(M, NOT_ARRIVED));

    // 각 칸의 현재 상태 (GREEN / RED / FLOWER)
    vector<vector<int>> cellState(N, vector<int>(M));
    
    queue<Coord> Q;

    // 배양액 확산 시작 위치 초기화
    for (int i = 0; i < (int)selectedPoints.size(); i++) {
        auto [x, y] = selectedPoints[i];
        arriveTime[x][y] = 0;
        cellState[x][y] = fertilizerType[i];
        Q.push(selectedPoints[i]);
    }

    while (!Q.empty()) {
        auto [x, y] = Q.front(); Q.pop();

        // 꽃이 생성된 경우 배양액 확산 불가
        if (cellState[x][y] == FLOWER) continue;

        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (isOutOfRange(nx, ny)) continue;
            if (garden[nx][ny] == LAKE) continue;

            // 아직 배양액이 도착하지 않은 경우
            if (arriveTime[nx][ny] == NOT_ARRIVED) {
                arriveTime[nx][ny] = arriveTime[x][y] + 1;
                cellState[nx][ny] = cellState[x][y];
                Q.push(make_pair(nx, ny));
            } else if ( // 같은 시간에 다른 종류의 배양액이 도착한 경우
                arriveTime[nx][ny] == arriveTime[x][y] + 1 &&
                cellState[nx][ny] != cellState[x][y] &&
                cellState[nx][ny] != FLOWER
            ) {
                cellState[nx][ny] = FLOWER; // 꽃 생성
                flowersCount++;
            }
        }
    }

    answer = max(answer, flowersCount);
}

// 선택된 위치에 배양액 배치
void assignFertiles(int index, int greenCount) {
    // 모든 위치에 배양액을 배치한 경우
    if (index == (int)selectedPoints.size()) {
        if (greenCount == G) simulate();
        return;
    }

    // 초록색 배양액 배치
    if (greenCount < G) {
        fertilizerType[index] = GREEN;
        assignFertiles(index + 1, greenCount + 1);
    }

    // 빨간색 배양액 배치
    if (index - greenCount < R) {
        fertilizerType[index] = RED;
        assignFertiles(index + 1, greenCount);
    }
}

// 배양액을 배치할 위치 조합 선택
void selectPositions(int start, int selectedCount) {
    // 배양액을 배치할 위치를 모두 선택한 경우
    if (selectedCount == G + R) {
        fertilizerType.assign(G + R, 0);
        assignFertiles(0, 0);
        return;
    }

    for (int i = start; i < (int)fertilePoints.size(); i++) {
        selectedPoints.push_back(fertilePoints[i]);
        selectPositions(i + 1, selectedCount + 1);
        selectedPoints.pop_back();
    }
}