#include <bits/stdc++.h>

using namespace std;

int main() {
    // 빠른 입출력 설정
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 100;
    int MAX_DIST = 10000;
    
    ostringstream oss;

    oss << N << "\n";

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) {
                oss << 0 << " ";
            } else if (i == N || j == N) {
                oss << 1 << " ";
            } else {
                oss << MAX_DIST << " ";
            }
        }

        oss << "\n";
    }

    cout << oss.str();

    return 0;
}