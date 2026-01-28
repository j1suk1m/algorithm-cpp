#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (int)1e5 * 2;

int N, C;
vector<int> houses(MAX_N);

// distance 이상 간격으로 C개의 공유기 설치 가능 여부 반환
bool canInstallRouters(int distance);

// 공유기 간 최소 거리의 최댓값을 매개변수 탐색으로 계산
int getMaxMinDistance();

int main() {
    // 빠른 입출력 설정
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> C;

    // 집 좌표 입력
    for (int i = 0; i < N; i++) {
        cin >> houses[i];
    }

    // 매개변수 탐색을 위한 정렬
    sort(houses.begin(), houses.begin() + N);

    cout << getMaxMinDistance();
    
    return 0;
}

bool canInstallRouters(int distance) {
    int prev = houses[0]; // 첫 번째 집에는 항상 공유기 설치
    int routerCount = 1;

    for (int i = 1; i < N; i++) {
        int curr = houses[i];

        // 이전에 설치한 공유기와의 거리가 distance 이상이면 설치
        if (curr - prev >= distance) {
            prev = curr;
            routerCount++;
        }
    }

    // 공유기 C개 이상 설치 가능하면 true 반환
    return routerCount >= C;
}

int getMaxMinDistance() {
    int left = 1;
    int right = houses[N - 1] - houses[0] + 1;

    while (left + 1 < right) {
        int mid = left + (right - left) / 2;

        if (canInstallRouters(mid)) { // mid 이상 간격으로 공유기 C개 설치 가능
            left = mid; // 간격을 늘려도 가능한지 확인
        } else { // mid 이상 간격으로 공유기 C개 설치 불가능
            right = mid; // 간격을 줄여서 더 많은 공유기 설치
        }
    }

    // 가능한 최대 거리
    return left;
}