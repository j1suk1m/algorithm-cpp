#include <bits/stdc++.h>

using namespace std;

int N;
vector<string> canvas;

// 프로토타입
void mark(int n, int x, int y);

int main() {
    cin >> N;
    canvas.resize(N, string(N, ' '));

    mark(N, 0, 0);

    for (const auto& line : canvas) {
        cout << line << "\n";
    }
    
    return 0;
}

void mark(int n, int x, int y) {
    if (n == 1) {
        canvas[x][y] = '*';
        return;
    }

    int sub = n / 3;
    
    for (int dx = 0; dx < 3; dx++) {
        for (int dy = 0; dy < 3; dy++) {
            // 가운데는 공백으로 유지
            if (dx == 1 && dy == 1) {
                continue;
            }
            
            mark(sub, x + dx * sub, y + dy * sub);
        }
    }
}