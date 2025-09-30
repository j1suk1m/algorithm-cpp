#include <vector>
#include <iostream>
#include <queue>

using namespace std;

vector<int> solution(vector<int> arr) {
    queue<int> queue;
    vector<int> answer;

    for (int i = 0; i < arr.size(); i++) {
        int curr = arr[i];
        
        if (queue.empty() || queue.back() != curr) {
            queue.push(curr);
        }
    }
    
    while (!queue.empty()) {
        answer.push_back(queue.front());
        queue.pop();
    }

    return answer;
}