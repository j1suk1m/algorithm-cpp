#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// str이 prefix로 시작하는지 확인
bool startsWith(const string& str, const string& prefix) {
    // 만약 str이 prefix보다 짧다면 prefix가 접두어일 수 없으므로 false 반환
    if (str.size() < prefix.size()) return false;

    // prefix와 str을 앞에서부터 비교 -> 처음으로 불일치하는 원소 쌍의 iterator 반환
    auto result = mismatch(prefix.begin(), prefix.end(), str.begin());
    
    // result.first == prefix.end()인 경우
    // -> prefix의 모든 문자가 str의 앞부분과 일치했다는 의미
    // -> 즉, str이 prefix로 시작하고, prefix는 str의 접두어
    return mismatch(prefix.begin(), prefix.end(), str.begin()).first == prefix.end();
}

bool solution(vector<string> phoneBook) {
    // 오름차순 정렬
    sort(phoneBook.begin(), phoneBook.end());
    
    // 접두어 존재 여부 확인
    for (int i = 0; i < (int)phoneBook.size() - 1; i++) {
        string curr = phoneBook[i];
        string next = phoneBook[i + 1];
        
        // curr이 next의 접두어인 경우 false 반환
        if (startsWith(next, curr)) {
            return false;
        }
    }
    
    // 접두어가 존재하지 않는 경우 true 반환
    return true;
}