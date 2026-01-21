#include <bits/stdc++.h>

using namespace std;

struct Compare {
    bool operator()(long long a, long long b) {
        return a > b;
    }
};

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        int K;
        cin >> K;

        priority_queue<long long, vector<long long>, Compare> pq;

        for (int j = 0; j < K; j++) {
            long long fileSize;
            cin >> fileSize;
            pq.push(fileSize);
        }

        long long answer = 0LL;

        while (pq.size() > 1) {
            long long firstMin = pq.top(); pq.pop();
            long long secondMin = pq.top(); pq.pop();

            answer += firstMin + secondMin;
            pq.push(firstMin + secondMin);
        }

        cout << answer << "\n";
    }
    
    return 0;
}