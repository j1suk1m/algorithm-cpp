#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    vector<int> temp;
    int i, j, k;
    
    for (const auto& command : commands) {
        i = command[0];
        j = command[1];
        k = command[2];
        
        vector<int> temp(array.begin() + i - 1, array.begin() + j); // i - 1 이상 j 미만
        sort(temp.begin(), temp.end());
        answer.push_back(temp[k - 1]);
    }
    
    return answer;
}