#include <bits/stdc++.h>

using namespace std;

// 프로토타입
int solve(int n, int r, int c);

int main() {
    int N, r, c;
    cin >> N >> r >> c;

    cout << solve(N, r, c);
    
    return 0;
}

int solve(int n, int r, int c) {
    // 기저 조건
    // 배열의 크기가 2 ^ n = 2 ^ 0 = 1일 때 방문 순서는 0
    if (n == 0) {
        return 0;
    }

    // 현재 배열을 좌상단, 우상단, 좌하단, 우하단의 2 * 2 크기 하위 배열로 분해했다고 가정
    int half = 1 << (n - 1); // 하위 배열의 한 변의 길이
    int area = half * half; // 하위 배열의 넓이

    // 좌상단 하위 배열에 (r, c)가 존재하는 경우
    if (r < half && c < half) {
        return solve(n - 1, r, c);
    }

    // 우상단 하위 배열에 (r, c)가 존재하는 경우
    if (r < half && c >= half) {
        return area + solve(n - 1, r, c - half);
    }

    // 좌하단 하위 배열에 (r, c)가 존재하는 경우
    if (r >= half && c < half) {
        return 2 * area + solve(n - 1, r - half, c);
    }

    // 우하단 하위 배열에 (r, c)가 존재하는 경우
    return 3 * area + solve(n - 1, r - half, c - half);
}