#include <bits/stdc++.h>

using namespace std;

// 최소 힙에서 사용할 구조체
struct Compare {
    bool operator()(int a, int b) {
        return a > b;
    }
};

priority_queue<int> maxHeap; // median 이하의 정수 저장 // 최상단에 항상 median이 위치
priority_queue<int, vector<int>, Compare> minHeap; // median을 초과하는 정수 저장

// 프로토타입
void rebalance();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int maxHeapSize = 0;
    int minHeapSize = 0;

    for (int i = 0; i < N; i++) {
        int number;
        cin >> number;

        // [1] 최대 힙 또는 최소 힙에 정수 push
        if (maxHeapSize == minHeapSize) { 
            maxHeap.push(number);
            maxHeapSize++;
        } else {
            minHeap.push(number);
            minHeapSize++;
        }

        // [2] 힙 균형 조정
        rebalance();

        // [3] median 출력
        cout << maxHeap.top() << "\n";
    }
    
    return 0;
}

void rebalance() {
    if (maxHeap.empty() || minHeap.empty()) {
        return;
    }
    
    // max(최대 힙) <= min(최소 힙)의 조건을 위반하는 경우
    if (maxHeap.top() > minHeap.top()) {
        int temp1 = maxHeap.top(); maxHeap.pop();
        int temp2 = minHeap.top(); minHeap.pop();

        maxHeap.push(temp2);
        minHeap.push(temp1);
    }
}