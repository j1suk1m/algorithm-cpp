#include <bits/stdc++.h>

using namespace std;

const int POP = 0;
const int EMPTY = 0;

struct Compare {
    bool operator()(int a, int b) {
        if (abs(a) != abs(b)) {
            return abs(a) > abs(b);
        }

        return a > b;
    }
};

int main() {
    int N;
    cin >> N;

    int x;
    priority_queue<int, vector<int>, Compare> pq; 
    
    for (int i = 0; i < N; i++) {
        cin >> x;

        if (x == POP) {
            if (pq.empty()) {
                cout << EMPTY << "\n";
            } else {
                cout << pq.top() << "\n";
                pq.pop();                
            }
        } else {
            pq.push(x);
        }
    }
    
    return 0;
}