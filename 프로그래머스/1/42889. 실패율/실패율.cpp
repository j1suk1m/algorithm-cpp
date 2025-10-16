#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<int> sort(const map<int, double>& m);

vector<int> solution(int N, vector<int> stages) {
    vector<int> playerCount(N + 1, 0);
    map<int, double> failureRate; // 스테이지별 실패율
    
    // 스테이지별 도전 중인 플레이어 수 저장
    for (int stage = 1; stage <= N; stage++) {
        playerCount[stage] = count(stages.begin(), stages.end(), stage);
    }
    
    int allPlayers = stages.size();
    
    // 스테이지별 실패율 계산
    for (int stage = 1; stage <= N; stage++) {
        if (allPlayers > 0) {
            failureRate[stage] = (double)playerCount[stage] / allPlayers;
            allPlayers -= playerCount[stage];
        } else {
            failureRate[stage] = 0.0;
        }
    }
    
    return sort(failureRate);
}

vector<int> sort(const map<int, double>& m) {
    vector<pair<int, double>> v(m.begin(), m.end());

    // value 내림차순, key 오름차순으로 정렬
    sort(v.begin(), v.end(), [](auto &a, auto &b) {
        if (a.second == b.second)
            return a.first < b.first; // key 오름차순
        return a.second > b.second;   // value 내림차순
    });

    vector<int> answer;
    
    // key(스테이지 번호) 정렬 순서대로 저장
    for (auto &p : v)
        answer.push_back(p.first);

    return answer;
}