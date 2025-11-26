#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Egg {
    int durability; // 내구도
    int weight; // 무게
    bool isBroken; // 깨짐 여부

    Egg(int durability, int weight) {
        this->durability = durability;
        this->weight = weight;
        this->isBroken = false;
    }

    // other로 this를 치는 함수
    void beHitBy(Egg& other) {
        this->durability -= other.weight;
        updateBrokenState();
    }

    // other로 this를 친 상태를 원복하는 함수
    void recover(Egg& other) {
        this->durability += other.weight;
        updateBrokenState();
    }

    void updateBrokenState() {
        if (this->durability <= 0) {
            this->isBroken = true;
        } else {
            this->isBroken = false;
        }
    }
};

int N;
int answer = 0;
vector<Egg> eggs;

void hitEggs(int currEggIndex, int brokenEggCount) {    
    if (currEggIndex == N) { // 맨 오른쪽 계란에 도달
        answer = max(answer, brokenEggCount);
        return;
    }

    if (eggs[currEggIndex].isBroken) { // 현재 계란이 깨진 경우
        hitEggs(currEggIndex + 1, brokenEggCount);
        return;
    }

    int count = 0; // 현재 계란으로 친 계란 횟수
    
    for (int i = 0; i < N; i++) {
        if (i == currEggIndex) continue;

        Egg& curr = eggs[currEggIndex];
        Egg& next = eggs[i];
        
        if (!next.isBroken) {
            count++;
            
            bool wasCurrBroken = curr.isBroken;
            bool wasNextBroken = next.isBroken;
            
            curr.beHitBy(next);
            next.beHitBy(curr);

            int newlyBrokenEggCount = 0;

            if (!wasCurrBroken && curr.isBroken) newlyBrokenEggCount++;
            if (!wasNextBroken && next.isBroken) newlyBrokenEggCount++;
            
            hitEggs(currEggIndex + 1, brokenEggCount + newlyBrokenEggCount);

            curr.recover(next);
            next.recover(curr);
        }
    }

    if (count == 0) { // 현재 계란으로 아무 계란도 치지 못한 경우
        hitEggs(currEggIndex + 1, brokenEggCount);        
    }
}

int main() {
    cin >> N;

    int S, W;

    // 계란 정보 저장
    for (int i = 0; i < N; i++) {
        cin >> S >> W;
        eggs.push_back(Egg(S, W));
    }

    if (N > 1) {
        hitEggs(0, 0);
    }

    cout << answer;

    return 0;
}