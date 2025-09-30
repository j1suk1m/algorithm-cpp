#include <string>
#include <vector>

using namespace std;

const int CONNECTION = 1;
const int MAX = 200;

vector<int> adjacentList[MAX];
bool visited[MAX];

// solution 아래에 선언하면 undeclared identifier 에러 발생
// 프로토타입 사용하거나, solution보다 먼저 선언해야 함
void runDfs(int curr) {
    visited[curr] = true;
    
    for (int next : adjacentList[curr]) {
        if (!visited[next]) {
            runDfs(next);
        }
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    // 양방향 연결 관계 저장
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && computers[i][j] == CONNECTION) {
                adjacentList[i].push_back(j);
                adjacentList[j].push_back(i);
            }
        }
    }
    
    // dfs를 이용한 네트워크 개수 계산
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            runDfs(i);
            answer++;
        }
    }
    
    return answer;
}