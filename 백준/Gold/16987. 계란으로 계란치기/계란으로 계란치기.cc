#include <iostream> // cin, cout
#include <vector> // vector
#include <algorithm> // max

using namespace std;

// 구조체
struct Egg {
    int strength;
    int weight;
    bool isBroken;

    Egg(int strength, int weight) {
        this->strength = strength;
        this->weight = weight;
        this->isBroken = false;
    }

    void updateBrokenStatus() {
        if (this->strength <= 0) {
            this->isBroken = true;
        } else {
            this->isBroken = false;
        }
    }
};

// 프로토타입
void hit(Egg&, Egg&);
void recover(Egg&, Egg&);
void hitEggs(int, int);

int N;
int answer;
vector<Egg> eggs;

int main() {
    cin >> N;

    int S, W;

    // 계란 저장
    for (int i = 0; i < N; i++) {
        cin >> S >> W;
        eggs.push_back(Egg(S, W));
    }

    int start = 0;
    int totalBrokenCount = 0;

    // 계란 치기
    hitEggs(start, totalBrokenCount);

    cout << answer;

    return 0;
}

void hit(Egg& curr, Egg& next) {
    curr.strength -= next.weight;
    next.strength -= curr.weight;

    curr.updateBrokenStatus();
    next.updateBrokenStatus();
}

void recover(Egg& curr, Egg& next) {
    curr.strength += next.weight;
    next.strength += curr.weight;

    curr.updateBrokenStatus();
    next.updateBrokenStatus();
}

void hitEggs(int currIndex, int totalBrokenCount) {
    if (currIndex == N) {
        answer = max(answer, totalBrokenCount);
        return;
    }

    Egg& curr = eggs[currIndex];

    if (curr.isBroken) {
        hitEggs(currIndex + 1, totalBrokenCount);
        return;
    }

    int hitCount = 0;

    // 손에 들고 있는 계란으로 다른 계란 치기
    for (int nextIndex = 0; nextIndex < N; nextIndex++) {
        if (nextIndex == currIndex) continue;

        Egg& next = eggs[nextIndex];

        if (next.isBroken) continue;

        // 새로 깨진 계란 개수를 집계하기 위해 계란 치기 전 상태 저장
        bool wasCurrBroken = curr.isBroken;
        bool wasNextBroken = next.isBroken;

        // 계란 치기
        hit(curr, next);
        hitCount++;

        int brokenCount = 0;

        // 새로 깨진 계란 개수 집계
        if (!wasCurrBroken && curr.isBroken) brokenCount++;
        if (!wasNextBroken && next.isBroken) brokenCount++;

        hitEggs(currIndex + 1, totalBrokenCount + brokenCount);

        // 계란 상태 원복
        recover(curr, next);
    }

    // 손에 들고 있는 계란으로 어떤 계란도 치지 못한 경우 다음 계란으로 이동
    if (hitCount == 0) {
        hitEggs(currIndex + 1, totalBrokenCount);
    }
}