#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Snowman {
    int height; // 두 눈덩이를 합해 만든 눈사람의 키
    int i; // 눈덩이 인덱스 1
    int j; // 눈덩이 인덱스 2

    Snowman(int height, int i, int j) {
        this->height = height;
        this->i = i;
        this->j = j;
    }
};

// 눈사람 키 기준 오름차순 정렬에 사용되는 비교 함수
bool compare(const Snowman& s1, const Snowman& s2) {
    return s1.height < s2.height;
}

// 두 눈사람이 같은 눈덩이를 공유하고 있는지 확인하는 함수
bool hasSameSnowball(const Snowman& s1, const Snowman& s2) {
    return s1.i == s2.i || s1.i == s2.j || s1.j == s2.i || s1.j == s2.j;
}

int main() {
    int N;
    cin >> N;

    vector<int> snowballs(N);

    // 눈덩이 저장
    for (int i = 0; i < N; i++) {
        int snowball;
        cin >> snowball;
        snowballs[i] = snowball;
    }

    vector<Snowman> snowmen;

    // 두 눈덩이를 합해 만들 수 있는 모든 눈사람 조합 계산
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) { // 항상 i < j 만족 -> 중복 제거
            int height = snowballs[i] + snowballs[j];
            snowmen.push_back(Snowman(height, i, j));
        }
    }

    // 눈사람 키 기준 오름차순 정렬
    sort(snowmen.begin(), snowmen.end(), compare);

    int snowmenCount = (int) snowmen.size();
    int right = 1; // 오른쪽 포인터
    int answer = snowmen[snowmenCount - 1].height;

    // 투 포인터 알고리즘 수행
    for (int left = 0; left < snowmenCount - 1; left++) {
        Snowman s1 = snowmen[left];

        for (int right = left + 1; right < snowmenCount; right++) {
            Snowman s2 = snowmen[right];
            int heightDifference = s2.height - s1.height;

            // 두 눈사람 키 차이로는 최솟값을 만들 수 없는 경우 탐색 조기 종료
            if (answer <= heightDifference) {
                break;
            }

            // 두 눈사람이 같은 눈덩이를 공유한 경우 다른 조합 탐색
            if (hasSameSnowball(s1, s2)) {
                continue;
            }

            answer = heightDifference;
        }
    }
   
    cout << answer;
    
    return 0;
}