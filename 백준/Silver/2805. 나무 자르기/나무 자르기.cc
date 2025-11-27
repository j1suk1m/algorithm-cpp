#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N; // 나무의 수, [1, 1e6]
int M; // 가져가려고 하는 나무의 길이, [1, 2 * 1e9]
vector<int> treeHeights; // 나무의 길이 벡터

bool check(int cutterHeight) {
    long long sum = 0LL;

    for (int i = N - 1; i >= 0; i--) {
        if (treeHeights[i] <= cutterHeight) break;

        sum += (long long)treeHeights[i] - cutterHeight;
    }

    return sum >= (long long)M;
}

int getCutterHeight() {
    int left = 0; // check(left) == true // 나무를 가져갈 수 있는 경우
    int right = treeHeights[N - 1]; // check(right) == false // 나무를 가져갈 수 없는 경우

    while (left + 1 < right) {
        int mid = left + (right - left) / 2; // (left + right) / 2와 동치, 오버플로 방지

        if (check(mid)) { // 가져갈 수 있는 나무의 길이가 M 이상 -> 절단기 높이를 높여도 M 이상 가져갈 수 있는지 확인
            left = mid;
        } else { // 가져갈 수 있는 나무의 길이가 M 미만 -> 절단기 높이를 낮춰 나무를 더 많이 자름
            right = mid;
        }
    }

    return left;
}

int main() {
    cin >> N >> M;

    // 나무 높이 저장
    for (int i = 0; i < N; i++) {
        int treeHeight;

        cin >> treeHeight;
        
        treeHeights.push_back(treeHeight);
    }

    // 이분 탐색을 위한 오름차순 정렬
    sort(treeHeights.begin(), treeHeights.end());

    // 이분 탐색을 이용한 절단기 최대 높이 계산
    int answer = getCutterHeight();

    cout << answer;
    
    return 0;
}