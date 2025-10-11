#include <iostream>
#include <vector>
#include <string>

using namespace std;

const string NEW_LINE = "\n";

int main() {
    // 입출력 최적화 세팅
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;
    vector<int> numbers = {0};

    cin >> N >> M;

    // N개의 수 저장
    for (int i = 0; i < N; i++) {
        int number;
        cin >> number;
        numbers.push_back(number);
    }

    vector<int> prefixSum(N + 1, 0);

    // 누적 합 계산
    for (int i = 1; i <= N; i++) {
        prefixSum[i] = prefixSum[i - 1] + numbers[i];
    }

    int start, end;
    string answer;

    // 구간 합 질의 명령 수행
    for (int i = 0; i < M; i++) {
        cin >> start >> end;
        answer += to_string(prefixSum[end] - prefixSum[start - 1]) + NEW_LINE;
    }

    cout << answer;
    
    return 0;
}