#include <vector>

using namespace std;

long long solution(int n, vector<int> times) {
    long long left = 0LL;
    long long right = (long long) n * times[(int) times.size() - 1];
    
    while (left + 1 < right) {
        long long mid = left - (left - right) / 2; // 전체 시간
        long long total = 0LL; // mid분 내에 심사를 받을 수 있는 사람의 수
        
        for (const int time : times) {
            total += mid / time;
        }
        
        if (total >= n) { // mid분 내에 n명 이상을 심사할 수 있는 경우
            right = mid; // 시간을 더 줄여도 되는지 탐색
        } else { // mid분 내에 n명 이상을 심사할 수 없는 경우
            left = mid; // 시간을 더 늘림
        }
    }
    
    return right;
}