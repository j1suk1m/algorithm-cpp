#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int answer = 0;
int N, K;
vector<string> words;
vector<int> wordMasks; // 단어를 비트마스크로 저장

void convertWordsToMasks();
bool canRead(int selectedMask, int wordMask);
int getReadableWordCount(int selectedMask);
void backtrack(int start, int count, int mask);

int main() {
    // 입출력 최적화 세팅
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;

    // 남극 언어의 단어 저장
    for (int i = 0; i < N; i++) {
        string word;
        cin >> word;
        words.push_back(word);
    }

    // 각 단어를 비트마스크로 변환
    convertWordsToMasks();

    // 백트래킹을 이용해 K개의 알파벳을 선택한 뒤, 읽을 수 있는 단어 개수의 최댓값 계산
    backtrack(0, 0, 0);

    // 결과 출력
    cout << answer;
    
    return 0;
}

void convertWordsToMasks() {
    for (const string& word : words) {
        int mask = 0;

        for (char ch : word) {
            mask |= (1 << (ch - 'a')); // 현재 알파벳을 마스크에 추가
        }

        wordMasks.push_back(mask);
    }
}

bool canRead(int selectedMask, int wordMask) {
    return (wordMask & selectedMask) == wordMask; // 단어에 포함된 모든 알파벳이 선택된 상태면 true
}

int getReadableWordCount(int selectedMask) {
    int count = 0;

    for (int wordMask : wordMasks) {
        if (canRead(selectedMask, wordMask)) {
            count++;
        }
    }

    return count;
}

void backtrack(int start, int count, int mask) {
    if (count == K) { // 종료 조건
        int count = getReadableWordCount(mask);
        answer = max(answer, count);
        return;
    }

    for (int i = start; i < 26; i++) {
        int nextMask = mask | (1 << i); // i번째 알파벳 선택
        backtrack(i + 1, count + 1, nextMask);
    }
}