#define Coord pair<int, int>
#define X first
#define Y second

#include <bits/stdc++.h>

using namespace std;

enum Color {
    NONE, GREEN, RED
};

enum Status {
    EMPTY,
    GREEN_ARRIVED,
    RED_ARRIVED,
    FLOWERED
};

const int NOT_ARRIVED = -1;
const int LAKE = 0;
const int LAND_FOR_APPLYING_CULTURE_MEDIUM = 2; // 배양액을 뿌릴 수 있는 땅

const vector<Coord> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int N, M, G, R;
int answer;

vector<vector<int>> garden;
vector<Coord> candidateCoords; // 배양액을 뿌릴 수 있는 모든 땅의 좌표
vector<Coord> selectedCoords; // 배양액을 뿌리기 위해 선택된 땅의 좌표
vector<Color> colors; // selectedCoords의 각 좌표에 뿌린 배양액의 색

// 프로토타입
bool isOutOfRange(int x, int y);
void spread();
void spray(int index, int greenCount);
void select(int index, int selectedCount, int candidateCount);

int main() {
    cin >> N >> M >> G >> R;

    // 정원 저장
    for (int x = 0; x < N; x++) {
        garden.push_back(vector<int>());

        for (int y = 0; y < M; y++) {
            int cell;
            cin >> cell;
            garden[x].push_back(cell);

            // 배양액을 뿌릴 수 있는 땅의 좌표 저장
            if (cell == LAND_FOR_APPLYING_CULTURE_MEDIUM) {
                candidateCoords.push_back({x, y});
            }
        }
    }

    int index = 0;
    int selectedCount = 0;
    int candidateCount = (int)candidateCoords.size();

    // 배양액 초기 위치 선정 및 확산
    select(index, selectedCount, candidateCount);

    cout << answer;

    return 0;
}

bool isOutOfRange(int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= M;
}

void spread() {
    queue<Coord> Q;
    vector<vector<int>> arrivalTime(N, vector<int>(M, NOT_ARRIVED));
    vector<vector<int>> status(N, vector<int>(M, EMPTY));

    for (int i = 0; i < (int)selectedCoords.size(); i++) {
        const Coord& curr = selectedCoords[i];
        Q.push(curr);
        arrivalTime[curr.X][curr.Y] = 0;

        if (colors[i] == GREEN) {
            status[curr.X][curr.Y] = GREEN_ARRIVED;
        } else {
            status[curr.X][curr.Y] = RED_ARRIVED;
        }
    }

    int flowerCount = 0;

    while (!Q.empty()) {
        const Coord& curr = Q.front(); Q.pop();

        if (status[curr.X][curr.Y] == FLOWERED) {
            continue;
        }

        for (const auto& [dx, dy] : dir) {
            int nx = curr.X + dx;
            int ny = curr.Y + dy;

            if (isOutOfRange(nx, ny)) continue;
            if (garden[nx][ny] == LAKE) continue;

            // 아직 배양액이 도달하지 않은 경우 현재 땅의 배양액 확산
            if (arrivalTime[nx][ny] == NOT_ARRIVED) {
                Q.push({nx, ny});
                arrivalTime[nx][ny] = arrivalTime[curr.X][curr.Y] + 1;
                status[nx][ny] = status[curr.X][curr.Y];
            } else if ( // 서로 다른 배양액이 동시에 도달한 경우 꽃 생성
                arrivalTime[nx][ny] == arrivalTime[curr.X][curr.Y] + 1 &&
                status[nx][ny] != status[curr.X][curr.Y] &&
                status[nx][ny] != FLOWERED
            ) {
                status[nx][ny] = FLOWERED;
                flowerCount++;
            }
        }
    }

    answer = max(answer, flowerCount);
}

void spray(int index, int greenCount) {
    // 종료 조건
    if (index == G + R) {
        if (greenCount == G) spread(); // 배양액 확산
        return;
    }

    // case 1: 초록색 배양액 뿌리기
    if (greenCount < G) {
        colors[index] = GREEN;
        spray(index + 1, greenCount + 1);
    }

    // case 2: 빨간색 배양액 뿌리기
    if (index - greenCount < R) {
        colors[index] = RED;
        spray(index + 1, greenCount);
    }
}

void select(int index, int selectedCount, int candidateCount) {
    // 종료 조건
    if (selectedCount == G + R) {
        colors.assign(G + R, NONE);
        spray(0, 0); // 배양액 뿌리기
        return;
    }

    // 조합
    for (int i = index; i < candidateCount; i++) {
        selectedCoords.push_back(candidateCoords[i]);
        select(i + 1, selectedCount + 1, candidateCount);
        selectedCoords.pop_back();
    }
}