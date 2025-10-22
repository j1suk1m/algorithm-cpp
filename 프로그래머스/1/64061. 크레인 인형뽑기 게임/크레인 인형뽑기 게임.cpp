#include <vector>
#include <stack>

using namespace std;

const int EMPTY = 0;

int solution(vector<vector<int>> board, vector<int> moves) {
    int n = (int)board.size();
    vector<stack<int>> screen(n + 1, stack<int>());
    stack<int> basket;
    
    // 2차원 정수 벡터 board -> 1차원 스택 벡터 screen
    for (int col = 0; col < n; col++) {
        for (int row = n - 1; row >= 0; row--) { // 거꾸로 넣어야 인형이 윗쪽부터 제거됨
            if (board[row][col] == EMPTY) continue; // 빈 칸은 스택에 넣지 않음
            screen[col + 1].push(board[row][col]);
        }
    }
    
    int answer = 0;
    
    for (int move : moves) {
        if (screen[move].empty()) continue; // 인형이 없는 곳에서 크레인을 작동시키는 경우 무시
        
        int doll = screen[move].top(); screen[move].pop(); // 인형을 집어 올림

        if (basket.empty() || basket.top() != doll) {
            basket.push(doll);
        } else { // 같은 인형 두 개가 바구니에 연속해서 쌓인 경우
            basket.pop();
            answer += 2; // 두 인형이 모두 사라짐
        }
    }
    
    return answer;
}