#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    map<string, int> map;
    
    // 맵에 <참여 선수 이름, 명수> 저장
    for (int i = 0; i < participant.size(); i++) {
        string name = participant[i];
        map[name]++;
    }
    
    // 완주한 선수 배열을 순회하며 명수 1씩 빼기
    for (int i = 0; i < completion.size(); i++) {
        string name = completion[i];
        map[name]--;
    }
    
    string answer = "";
    
    // 완주하지 못한 선수 찾기
    for (auto it = map.begin(); it != map.end(); it++) {
        if (it->second > 0) {
            answer = it->first;
            break;
        }
    }
    
    return answer;
}