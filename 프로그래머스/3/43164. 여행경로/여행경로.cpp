#include <string>
#include <vector>

using namespace std;

/*
- 사전 순으로 앞서는 최종 경로
- 모든 공항 이름이 알파벳 대문자로 이루어져 있고, answer의 초깃값인 알파벳 소문자의 아스키 코드 값이 알파벳 대문자보다 항상 큼
- 따라서 backtrack 함수의 종료 조건에서 answer와 route를 최초 비교할 때 answer가 무조건 갱신되는 효과가 발생함
*/
vector<string> answer = {"a"};

const string START = "ICN"; // 출발 공항
vector<string> route = {START}; // 백트래킹으로 조합한 경로
vector<bool> used; // 티켓 사용 여부 // resize 필요

void backtrack(const vector<vector<string>>&, int, string);

vector<string> solution(vector<vector<string>> tickets) {   
    used.resize(tickets.size(), false); // 런타임에 크기와 초깃값 설정
    backtrack(tickets, 0, START);
    return answer;
}

void backtrack(const vector<vector<string>>& tickets, int usedTicketCount, string curr) {
    if (answer < route) return; // 현재 경로가 사전 순으로 절대 앞설 수 없는 경우 조기 종료
    if (usedTicketCount == tickets.size()) {  // 모든 항공권을 사용한 경우 종료
        answer = route; 
        return;
    }
    
    for (int i = 0; i < tickets.size(); i++) {
        if (used[i]) continue;
        if (tickets[i][0] != curr) continue;
        
        used[i] = true;
        route.push_back(tickets[i][1]);
        backtrack(tickets, usedTicketCount + 1, tickets[i][1]);
        route.pop_back();
        used[i] = false;
    }
}