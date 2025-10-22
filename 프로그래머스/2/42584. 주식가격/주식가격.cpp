#include <vector>
#include <stack>

using namespace std;

struct Stock {
    int price; // 가격
    int second; // 가격이 떨어지지 않은 시간(초)
    
    Stock(int price, int second) {
        this->price = price;
        this->second = second;
    }
};

vector<int> solution(vector<int> prices) {
    vector<int> answer((int)prices.size(), 0);
    stack<Stock> s;
    
    // 맨 마지막 가격은 항상 0초 동안 가격이 떨어지지 않으므로 그 앞 가격부터 거꾸로 순회
    for (int i = (int)answer.size() - 2; i >= 0; i--) {
        int currPrice = prices[i];
        int currSecond = 1;
        
        // 가격이 떨어지지 않은 기간이 몇 초인지 계산
        while (!s.empty() && s.top().price >= currPrice) {
            currSecond += s.top().second;
            s.pop();
        }
        
        s.push(Stock(currPrice, currSecond));
        answer[i] = currSecond;
    }

    return answer;
}