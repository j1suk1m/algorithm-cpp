#include <bits/stdc++.h>

using namespace std;

struct Compare {
    bool operator()(int a, int b) {
        return a > b;
    }
};

int main() {
    int N;
    cin >> N;

    int sum = 0;
    int cardSize;
    priority_queue<int, vector<int>, Compare> pq;

    // 카드 묶음 크기 저장
    for (int i = 0; i < N; i++) {
        cin >> cardSize;
        pq.push(cardSize);
    }

    while (pq.size() > 1) {
        int firstMin = pq.top(); pq.pop();
        int secondMin = pq.top(); pq.pop();

        pq.push(firstMin + secondMin);
        sum += firstMin + secondMin;
    }

    cout << sum;
    
    return 0;
}