#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridgeLength, int weight, vector<int> truckWeights) {
    int time = 0;
    int totalWeight = 0;
    queue<int> bridge;
    queue<int> trucks;
    
    for (int i = 0; i < truckWeights.size(); i++) {
        trucks.push(truckWeights[i]);
    }
    
    for (int i = 0; i < bridgeLength; i++) {
        bridge.push(0);
    }

    while (!trucks.empty()) {
        time++;
        
        int curr = trucks.front();
        
        // 다리 맨 앞에 있는 트럭이 다리를 지남
        totalWeight -= bridge.front();
        bridge.pop();
        
        // 현재 트럭이 다리 위로 올라가도 무게 제한에 걸리지 않으면 올리고, 아니면 무게 0인 트럭을 올림
        if (totalWeight + curr <= weight) {
            totalWeight += curr;
            bridge.push(curr);
            trucks.pop();            
        } else {
            bridge.push(0);
        }
    }
    
    // 다리 길이만큼의 시간을 더해야 마지막 트럭이 다리를 완전히 지남
    return time + bridgeLength;
}