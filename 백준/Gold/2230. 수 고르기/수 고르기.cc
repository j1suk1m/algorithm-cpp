#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;

    cin >> N >> M;

    vector<int> arr;
    int number;

    // 수열 저장
    for (int i = 0; i < N; i++) {
        cin >> number;
        arr.push_back(number);
    }

    // 수열 오름차순 정렬
    sort(arr.begin(), arr.end());

    int left = 0;
    int right = 0;
    int answer = (int)1e9 * 2; // M의 최댓값으로 초기화

    // 투 포인터 알고리즘 수행
    // 동일한 위치에 있는 수를 두 번 고를 수 있으므로, left == right인 경우 포함
    while (left <= right && right < N) {
        int diff = arr[right] - arr[left];

        if (diff < M) {
            right++;
        } else {
            answer = min(answer, diff);
            left++;
        } 
    }

    cout << answer;
    
    return 0;
}