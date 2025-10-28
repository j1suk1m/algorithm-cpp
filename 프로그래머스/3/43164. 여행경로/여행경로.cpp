#include <string>
#include <vector>

using namespace std;

const int SRC = 0;
const int DEST = 1;
const string DUMMY = "a";
const string START = "ICN";

vector<string> answer = {DUMMY};
vector<string> route = {START};
vector<bool> used;

void backtrack(int count, string curr, const vector<vector<string>>& tickets);

vector<string> solution(vector<vector<string>> tickets) {
    used.resize((int)tickets.size(), false);
    
    backtrack(0, START, tickets);
    
    return answer;
}

void backtrack(int count, string curr, const vector<vector<string>>& tickets) {
    if (count == (int)tickets.size()) {
        if (answer > route) {
            answer = route;
        }
        
        return;
    }
    
    for (int nextIdx = 0; nextIdx < (int)tickets.size(); nextIdx++) {
        if (!used[nextIdx] && curr == tickets[nextIdx][SRC]) {
            used[nextIdx] = true;
            route.push_back(tickets[nextIdx][DEST]);
            backtrack(count + 1, tickets[nextIdx][DEST], tickets);
            route.pop_back();
            used[nextIdx] = false;
        }
    }
}