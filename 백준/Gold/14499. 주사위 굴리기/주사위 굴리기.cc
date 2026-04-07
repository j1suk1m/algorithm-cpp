#include <bits/stdc++.h>

using namespace std;

int N, M;

const int EAST = 1;
const int WEST = 2;
const int NORTH = 3;
const int SOUTH = 4;

const int dx[] = {0, 0, 0, -1, 1}; // dummy, 동, 서, 북, 남
const int dy[] = {0, 1, -1, 0, 0}; // dummy, 동, 서, 북, 남

bool isOutOfRange(int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= M;
}

int main() {
    // 빠른 입출력 설정
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y, K;

    cin >> N >> M >> x >> y >> K;

    vector<vector<int>> maps(N, vector<int>(M));

    // 지도 저장
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> maps[i][j];
        }
    }

    int command;
    ostringstream oss;
    array<int, 6> dice = {0, 0, 0, 0, 0, 0}; // 상, 북, 동, 서, 남, 하
    
    // 명령 수행
    for (int i = 0; i < K; i++) {
        cin >> command;

        int nx = x + dx[command];
        int ny = y + dy[command];

        // 범위 벗어나는 경우 무시
        if (isOutOfRange(nx, ny)) {
            continue;
        }

        auto temp = dice;

        // 주사위 이동
        if (command == EAST) {
            dice = {temp[3], temp[1], temp[0], temp[5], temp[4], temp[2]};
        } else if (command == WEST) {
            dice = {temp[2], temp[1], temp[5], temp[0], temp[4], temp[3]};
        } else if (command == NORTH) {
            dice = {temp[4], temp[0], temp[2], temp[3], temp[5], temp[1]};
        } else if (command == SOUTH) {
            dice = {temp[1], temp[5], temp[2], temp[3], temp[0], temp[4]};
        }

        if (maps[nx][ny] == 0) {
            maps[nx][ny] = dice[5];
        } else {
            dice[5] = maps[nx][ny];
            maps[nx][ny] = 0;
        }

        oss << dice[0] << "\n";

        x = nx;
        y = ny;
    }

    cout << oss.str();
    
    return 0;
}