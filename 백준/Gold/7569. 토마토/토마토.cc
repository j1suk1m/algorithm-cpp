#include <bits/stdc++.h>

using namespace std;

struct Node {
    int row;
    int column;
    int height;
    int day;

    Node(int row, int column, int height, int day) {
        this->row = row;
        this->column = column;
        this->height = height;
        this->day = day;
    }
};

const int RIPE_TOMATO = 1;
const int UNRIPE_TOMATO = 0;
const int EMPTY = -1;

const vector<tuple<int, int, int>> dir = {
    {-1, 0, 0}, {1, 0, 0},
    {0, -1, 0}, {0, 1, 0}, 
    {0, 0, -1}, {0, 0, 1} 
};

int N, M, H;

// 프로토타입
int getMinDay(vector<vector<vector<int>>>&, queue<Node>&, int);

int main() {
    cin >> M >> N >> H;

    queue<Node> Q;
    int unripeTomatoCount = 0;
    vector<vector<vector<int>>> box(H, vector<vector<int>>(N, vector<int>(M)));

    // 토마토 상자 정보 저장
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                cin >> box[i][j][k];

                if (box[i][j][k] == RIPE_TOMATO) { // 익은 토마토인 경우
                    Q.push(Node(j, k, i, 0));
                } else if (box[i][j][k] == UNRIPE_TOMATO) { // 익지 않은 토마토인 경우
                    unripeTomatoCount++;
                }
            }
        }
    }

    int minDay = 0;
    
    if (unripeTomatoCount > 0) {
        minDay = getMinDay(box, Q, unripeTomatoCount);
    }
    
    cout << minDay;

    return 0;
}

// 너비 우선 탐색으로 모든 토마토가 익는 최소 일수 계산
int getMinDay(vector<vector<vector<int>>>& box, queue<Node>& Q, int unripeTomatoCount) {
    int lastDay = 0;
    
    while (!Q.empty()) {
        Node curr = Q.front(); Q.pop();

        for (auto [dx, dy, dz] : dir) {
            int nx = curr.row + dx;
            int ny = curr.column + dy;
            int nz = curr.height + dz;
            
            if (nx < 0 || nx >= N || ny < 0 || ny >= M || nz < 0 || nz >= H) {
                continue;
            }

            if (box[nz][nx][ny] == UNRIPE_TOMATO) {
                Q.push(Node(nx, ny, nz, curr.day + 1));
                box[nz][nx][ny] = RIPE_TOMATO;
                unripeTomatoCount--;
                lastDay = curr.day + 1;
            }
        }
    }

    return unripeTomatoCount == 0 ? lastDay : -1;
}