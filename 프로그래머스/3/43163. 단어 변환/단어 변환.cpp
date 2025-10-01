#include <string>
#include <vector>
#include <algorithm> // find()
#include <queue>

using namespace std;

struct Word {
    string content;
    int count;
    
    Word(string content) : Word(content, 0) {} // this(content, 0); 사용 불가
    
    Word(string content, int count) {
        this->content = content;
        this->count = count;
    }
};

bool canConvertInto(string s1, string s2) {
    int diffCount = 0;
    
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] != s2[i]) diffCount++;
        if (diffCount > 1) return false;
    }
    
    return diffCount == 1;
}

int bfs(string begin, string target, const vector<string>& words) {
    queue<Word> q;
    vector<bool> visited(words.size(), false);
    
    q.push(Word(begin));
    
    while (!q.empty()) {
        Word curr = q.front();
        q.pop();
        
        if (curr.content == target) {
            return curr.count;
        }
        
        for (int i = 0; i < words.size(); i++) {
            string next = words[i];
            
            if (!visited[i] && canConvertInto(curr.content, next)) {
                q.push(Word(next, curr.count + 1));
                visited[i] = true;
            }
        }
    }
    
    return 0;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    
    // target이 words 안에 있는 경우
    if (find(words.begin(), words.end(), target) != words.end()) {
        answer = bfs(begin, target, words);
    }
    
    return answer;
}