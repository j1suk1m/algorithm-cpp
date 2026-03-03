#include <bits/stdc++.h>

using namespace std;

int N;
vector<string> canvas;

// 프로토타입
void mark(int n, int x, int y);

int main() {
    cin >> N;
    canvas.resize(N, string(2 * N - 1, ' '));

    mark(N, 0, N - 1);

    for (const auto& line : canvas) {
        cout << line << "\n";
    }
    
    return 0;
}

void mark(int n, int x, int y) {
    // 기저 조건
    // 삼각형 높이가 3 * 2^k 형태이므로 최소 삼각형 높이는 3
    if (n == 3) {
        canvas[x][y] = '*';
        canvas[x + 1][y - 1] = '*';
        canvas[x + 1][y + 1] = '*';

        for (int dy = -2; dy <= 2; dy++) {
            canvas[x + 2][y + dy] = '*';
        }
        
        return;
    }

    int sub = n / 2;
    
    // 위쪽 삼각형
    mark(sub, x, y);

    // 왼쪽 아래 삼각형
    mark(sub, x + sub, y - sub);

    // 오른쪽 아래 삼각형
    mark(sub, x + sub, y + sub);
}