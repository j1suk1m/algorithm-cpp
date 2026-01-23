#include <bits/stdc++.h>

using namespace std;

struct Problem {
    int deadline;
    int count;

    Problem(int deadline, int count) {
        this->deadline = deadline;
        this->count = count;
    }

    bool operator<(const Problem& other) const {
        if (deadline != other.deadline) {
            return deadline > other.deadline; // 데드라인 오름차순
        }
        
        return count < other.count; // 컵라면 개수 내림차순
    }
};

struct Compare {
    bool operator()(int a, int b) {
        return a > b;
    }
};

int main() {
    int N;
    cin >> N;

    // 데드라인은 오름차순, 컵라면 개수는 내림차순으로 문제를 저장하는 우선순위 큐
    priority_queue<Problem> problems;

    // 문제 저장
    for (int i = 0; i < N; i++) {
        int deadline, count;
        cin >> deadline >> count;
        problems.push(Problem(deadline, count));
    }

    // 문제를 풀어서 얻은 컵라면 개수를 오름차순으로 저장하는 우선순위 큐
    priority_queue<int, vector<int>, Compare> counts;
    
    while (!problems.empty()) {
        Problem problem = problems.top(); problems.pop();

        if (problem.deadline > (int)counts.size()) { // 현재 문제를 풀 수 있는 경우
            counts.push(problem.count); // 푼 것으로 간주하고 컵라면 개수 추가
        } else if (problem.count > counts.top()) { // 가장 적은 컵라면을 받은 문제를 제거하고 현재 문제를 풀지 확인
            counts.pop();
            counts.push(problem.count);
        }
    }

    int answer = 0;

    // 컵라면 개수 누적
    while (!counts.empty()) {
        answer += counts.top();
        counts.pop();
    }

    cout << answer << endl;
    
    return 0;
}