#include <iostream> // cin, cout
#include <vector> // vector
#include <numeric> // accumulate
#include <algorithm> // sort

using namespace std;

int L, C;
vector<string> alphabets;
vector<string> selectedAlphabets;

const int VOWELS_MIN_COUNT = 1;
const int CONSONANTS_MIN_COUNT = 2;

// 프로토타입
bool isVowel(char);
bool isValidPassword(string);
void generatePassword(int, int);

int main() {
    cin >> L >> C;

    string alphabet;

    // 알파벳 저장
    for (int i = 0; i < C; i++) {
        cin >> alphabet;
        alphabets.push_back(alphabet);
    }

    // 알파벳 사전순 정렬
    sort(alphabets.begin(), alphabets.end());

    // 유효한 암호 생성
    generatePassword(0, 0);

    return 0;
}

bool isVowel(char ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

bool isValidPassword(string password) {
    int vowelsCount = 0;
    int consonantsCount = 0;

    for (char ch : password) {
        if (isVowel(ch)) {
            vowelsCount++;
        } else {
            consonantsCount++;
        }
    }

    return vowelsCount >= VOWELS_MIN_COUNT && consonantsCount >= CONSONANTS_MIN_COUNT;
}

void generatePassword(int start, int selectedCount) {
    if (selectedCount == L) {
        // vector<string> -> string 변환
        string password = accumulate(
            selectedAlphabets.begin(),
            selectedAlphabets.end(),
            string{}
        );

        // 유효한 암호일 경우 출력
        if (isValidPassword(password)) {
            cout << password << "\n";
        }

        return;
    }

    for (int i = start; i < C; i++) {
        selectedAlphabets.push_back(alphabets[i]);
        generatePassword(i + 1, selectedCount + 1);
        selectedAlphabets.pop_back();
    }
}