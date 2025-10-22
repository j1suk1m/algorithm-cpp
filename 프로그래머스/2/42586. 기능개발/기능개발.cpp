#include <vector>
#include <queue>

#define CEIL(a, b) (((a) + (b) - 1) / (b))

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<int> q;
    int taskCount = (int)progresses.size();
    
    // 큐에 작업당 배포 가능한 날짜 저장
    for (int i = 0; i < taskCount; i++) {
        q.push(CEIL(100 - progresses[i], speeds[i]));
    }
    
    // 첫번째 작업 배포
    int deploymentCount = 1;
    int day = q.front(); q.pop();
    
    while (!q.empty()) {
        int targetDay = q.front(); q.pop();
        
        if (day >= targetDay) { // 현재 날짜에 작업을 바로 배포할 수 있는 경우
            deploymentCount++;
        } else {
            answer.push_back(deploymentCount);
            deploymentCount = 1;
            day = targetDay;
        }
    }
    
    answer.push_back(deploymentCount);
    
    return answer;
}