#define Line pair<int, int>
#define Start first
#define End second
#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e9 + 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    vector<Line> lines(N);
    
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        lines[i] = {x, y};    
    }

    // 시작 지점 기준 오름차순 정렬
    sort(lines.begin(), lines.end(), [](auto &x, auto &y) {
        return x.Start < y.Start;
    });

    int totalLength = 0;
    int start = -INF;
    int end = -INF;
    
    for (auto& curr : lines) {
        if (curr.Start <= end) { // 겹쳐서 그릴 수 있는 경우
            end = max(end, curr.End);
        } else { // 겹쳐서 그릴 수 없는 경우
            totalLength += end - start;
            start = curr.Start;
            end = curr.End;
        }
    }

    totalLength += end - start;

    cout << totalLength;
    
    return 0;
}