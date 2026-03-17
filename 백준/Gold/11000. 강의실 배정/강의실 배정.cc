#define Lecture pair<int, int>
#define Start first
#define End second
#include <bits/stdc++.h>

using namespace std;

int main() {
    // 빠른 입출력 설정
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Lecture> lectures(N);

    for (int i = 0; i < N; i++) {
        int S, T;
        cin >> S >> T;
        lectures[i] = {S, T};
    }

    // 시작 시간을 기준으로 오름차순 정렬
    sort(lectures.begin(), lectures.end(), [](auto& a, auto& b) {
        return a.Start < b.Start;
    });

    priority_queue<int, vector<int>, greater<int>> PQ;
    
    Lecture firstLecture = lectures[0];
    PQ.push(firstLecture.End);

    for (int i = 1; i < N; i++) {
        auto [start, end] = lectures[i];
        
        if (start < PQ.top()) { // 새 강의실을 사용해야 하는 경우
            PQ.push(end);
        } else { // 현재 강의실을 사용할 수 있는 경우
            PQ.pop();
            PQ.push(end);
        }
    }

    cout << PQ.size();
    
    return 0;
}