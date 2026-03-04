#include <bits/stdc++.h>

using namespace std;

ostringstream sb;

// 프로토타입
void move(int src, int dest);
int solve(int n, int src, int dest, int temp);

int main() {
    int N;
    cin >> N;

    int src = 1;
    int temp = 2;
    int dest = 3;
    
    int K = solve(N, src, dest, temp);

    cout << K << "\n";
    cout << sb.str();
    
    return 0;
}

void move(int src, int dest) {
    sb << src << " " << dest << "\n"; 
}

// n개의 원반을 시작 장대 src에서 도착 장대 dest로 이동
int solve(int n, int src, int dest, int temp) {
    if (n == 1) {
        move(src, dest);
        return 1;
    }

    int count = 0;

    // n - 1개의 원반을 시작 장대에서 임시 장대로 이동
    count += solve(n - 1, src, temp, dest);

    // 가장 큰 원반을 시작 장대에서 도착 장대로 이동
    count += 1;
    move(src, dest);

    // n - 1개의 원반을 임시 장대에서 도착 장대로 이동
    count += solve(n - 1, temp, dest, src);

    return count;
}