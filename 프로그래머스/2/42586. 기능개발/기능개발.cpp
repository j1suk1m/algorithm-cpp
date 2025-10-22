#include <string>
#include <vector>
#include <queue>

#define CEIL(a, b) (((a) + (b) - 1) / (b))

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<pair<int, int>> q;
    
    // 큐에 작업 진도, 개발 속도 저장
    for (int i = 0; i < (int)progresses.size(); i++) {
        q.push(make_pair(progresses[i], speeds[i]));
    }
    
    int deploymentCount = 0;
    int day = 1;
    
    while (!q.empty()) {
        auto [progress, speed] = q.front(); q.pop();
        
        if (100 - progress <= speed * day) {
            deploymentCount++;
        } else {
            if (deploymentCount > 0) answer.push_back(deploymentCount);                
            
            deploymentCount = 1;
            day = CEIL(100 - progress, speed);
        }
    }
    
    if (deploymentCount > 0) {
        answer.push_back(deploymentCount);
    }
    
    return answer;
}