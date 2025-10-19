#include <string>
#include <vector>

using namespace std;

bool isValid(int width, int height, int brown, int yellow);

vector<int> solution(int brown, int yellow) {
    vector<int> answer(2, 0);
    int totalArea = brown + yellow;
    
    for (int width = totalArea; width > 0; width--) {
        int height = totalArea / width;
        
        if (totalArea % height != 0) continue;
        if (!isValid(width, height, brown, yellow)) continue;
        
        answer[0] = width;
        answer[1] = height;
        break;
    }
    
    return answer;
}

bool isValid(int width, int height, int brown, int yellow) {
    return (2 * width + 2 * height - 4 == brown) && ((width - 2) * (height - 2) == yellow);
}