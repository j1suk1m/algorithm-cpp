#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {
    const vector<int> first = {1, 2, 3, 4, 5};
    const vector<int> second = {2, 1, 2, 3, 2, 4, 2, 5};
    const vector<int> third = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    const int TOTAL = 3;
    const int FIRST = 0;
    const int SECOND = 1;
    const int THIRD = 2;
    const int FIRST_SIZE = first.size();
    const int SECOND_SIZE = second.size();
    const int THIRD_SIZE = third.size();
    vector<int> scores(TOTAL, 0);
    
    // 점수 누적
    for (int i = 0; i < answers.size(); i++) {
        int answer = answers[i];
        
        if (first[i % FIRST_SIZE] == answer) {
            scores[FIRST]++;
        }
        
        if (second[i % SECOND_SIZE] == answer) {
            scores[SECOND]++;
        }
        
        if (third[i % THIRD_SIZE] == answer) {
            scores[THIRD]++;
        }        
    }
    
    int maxScore = *max_element(scores.begin(), scores.end()); // iterator 반환 -> * 연산자로 역참조 필요
    vector<int> answer;
    
    // 가장 많은 문제를 맞힌 사람을 오름차순으로 저장
    for (int i = 0; i < TOTAL; i++) {
        if (scores[i] == maxScore) {
            answer.push_back(i + 1);
        }
    }
    
    return answer;
}