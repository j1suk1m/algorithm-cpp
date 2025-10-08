#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    for (vector<int>& command : commands) {        
        int i = command[0];
        int j = command[1];
        int k = command[2];
        
        vector<int> temp(array.begin() + i - 1, array.begin() + j); // 범위 복사
        sort(temp.begin(), temp.end()); // 복사본 정렬
 
        answer.push_back(temp[k - 1]);
    }
    
    return answer;
}