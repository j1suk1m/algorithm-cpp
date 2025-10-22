#include <string>
#include <vector>
#include <queue>

using namespace std;

const string YES = "Yes";
const string NO = "No";

queue<string> saveCardsToQueue(const vector<string>& cards);
bool canUseRemainingCards(queue<string>& q, const vector<string>& goal, int goalLen, int goalIdx);

string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) {
    queue<string> q1 = saveCardsToQueue(cards1);
    queue<string> q2 = saveCardsToQueue(cards2); 
    
    int goalLen = (int)goal.size();
    int goalIdx = 0;
    
    while (!q1.empty() && !q2.empty() && goalIdx < goalLen) {
        string currGoal = goal[goalIdx];
        string card1 = q1.front();
        string card2 = q2.front();
        
        if (currGoal == card1) {
            q1.pop();
            goalIdx++;
        } else if (currGoal == card2) {
            q2.pop();
            goalIdx++;
        } else { // 두 카드 뭉치를 모두 사용해도 현재 단어를 만들 수 없는 경우 NO 반환
            return NO;
        }
    }
    
    if (goalIdx == goalLen) { // goal을 만들 수 있는 경우 YES 반환
        return YES;
    }
    
    // 두 큐 중 하나만 남은 경우, 남은 카드로 goal을 만들 수 있다면 YES 반환
    if ((!q1.empty() && canUseRemainingCards(q1, goal, goalLen, goalIdx)) ||
       (!q2.empty() && canUseRemainingCards(q2, goal, goalLen, goalIdx))) {
        return YES;
    } 
    
    return NO;
}

// cards에 저장된 카드들을 큐에 저장한 뒤 반환
queue<string> saveCardsToQueue(const vector<string>& cards) {
    queue<string> q;
    
    for (const string& card : cards) {
        q.push(card);
    }
    
    return q;
}

// 남은 카드를 사용해서 goal을 만들 수 있는지 반환
bool canUseRemainingCards(queue<string>& q, const vector<string>& goal, int goalLen, int goalIdx) {
    while (!q.empty() && goalIdx < goalLen) {
        if (goal[goalIdx] != q.front()) {
            return false;
        } else {
            q.pop();
            goalIdx++;
        }
    }   
    
    return true;
}