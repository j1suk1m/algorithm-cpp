#include <string>
#include <vector>

using namespace std;

int backtrack(vector<int>& numbers, int idx, int result, int target) {
    if (idx == numbers.size() - 1) {
        return result == target ? 1 : 0;
    }
    
    int minusResult = backtrack(numbers, idx + 1, result - numbers[idx + 1], target);
    int plusResult = backtrack(numbers, idx + 1, result + numbers[idx + 1], target);
    
    return minusResult + plusResult;
    
}

int solution(vector<int> numbers, int target) {
    return backtrack(numbers, -1, 0, target);
}