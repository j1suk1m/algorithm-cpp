#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 8;

int answer = 0;
vector<bool> visited(MAX, false);

void backtrack(int count, int curr, const vector<vector<int>>& dungeons);

int solution(int k, vector<vector<int>> dungeons) {
    backtrack(0, k, dungeons);
    return answer;
}

void backtrack(int count, int curr, const vector<vector<int>>& dungeons) {
    answer = max(answer, count);
    
    for (int i = 0; i < (int)dungeons.size(); i++) {
        if (!visited[i] && curr >= dungeons[i][0]) {
            visited[i] = true;
            backtrack(count + 1, curr - dungeons[i][1], dungeons);
            visited[i] = false;
        }
    }
}