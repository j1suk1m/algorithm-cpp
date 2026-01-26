#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (int)1e6;

int N;
long long M;

vector<int> trees(MAX_N);

// 프로토타입
bool isPossible(int height);
int findMaxHeight();

int main() {
    cin >> N >> M;

    // 나무 높이 저장
    for (int i = 0; i < N; i++) {
        cin >> trees[i];
    }

    // 나무 높이 오름차순 정렬
    sort(trees.begin(), trees.begin() + N);

    // 절단기 높이의 최댓값 계산
    int maxHeight = findMaxHeight();

    cout << maxHeight;

    return 0;
}

bool isPossible(int height) {
    long long sum = 0LL; // int 오버플로 방지

    // trees는 오름차순 정렬된 상태
    // 뒤에서부터 순회하며 height 초과하는 나무만 계산
    for (int i = N - 1; i >= 0; i--) {
        if (trees[i] <= height) {
            break; // 이후부터는 모두 height 이하이므로 누적 계산 불필요
        }

        sum += (long long)trees[i] - height;
    }

    // 절단기 높이가 height일 때 얻을 수 있는 나무의 총 길이가
    // 목표 길이 M을 충족하는지 확인
    return sum >= M;
}

int findMaxHeight() {
    int left = 0; // isPossible(left) == true
    int right = trees[N - 1]; // isPossible(right) == false

    while (left + 1 < right) {
        // left와 right 사이에서
        // 조건을 만족하는 절단기 최대 높이를 좁혀나감
        int mid = left + (right - left) / 2; // (left + right) / 2와 동일

        if (isPossible(mid)) {
            // 절단기 높이가 mid일 때 목표 길이 M을 얻을 수 있다면
            // 절단기 높이를 높여 나무를 더 적게 잘라도 M을 얻을 수 있는지 확인
            left = mid;
        } else {
            // 절단기 높이가 mid일 때 목표 길이 M을 얻을 수 없으므로
            // 절단기 높이를 낮춰 나무를 더 많이 자름
            right = mid;
        }
    }

    return left;
}