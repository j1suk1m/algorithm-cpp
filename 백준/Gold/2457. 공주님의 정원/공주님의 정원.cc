#define Date pair<int, int>
#define Month first
#define Day second
#include <bits/stdc++.h>

using namespace std;

struct Flower {
    Date start;
    Date end;

    Flower(int startMonth, int startDay, int endMonth, int endDay) {
        this->start = {startMonth, startDay};
        this->end = {endMonth, endDay};
    }
};

int main() {
    // 빠른 입출력 설정
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Flower> flowers;

    for (int i = 0; i < N; i++) {
        int startMonth, startDay, endMonth, endDay;
        cin >> startMonth >> startDay >> endMonth >> endDay;
        flowers.emplace_back(startMonth, startDay, endMonth, endDay);
    }

    // 꽃이 피는 날짜 기준 오름차순 정렬
    sort(flowers.begin(), flowers.end(), [](const auto& a, const auto& b) {
        return a.start < b.start;
    });

    Date curr = {3, 1};
    Date target = {11, 30};

    int i = 0;
    int count = 0;

    // 현재 날짜 curr까지 피기 시작한 꽃들 중에서
    // 가장 늦게 지는 꽃을 선택해 꽃이 피어 있는 구간을 최대한 확장하는 전략
    while (curr <= target) {
        Date temp = curr;

        // 현재 날짜 curr까지 피기 시작한 꽃을 모두 확인하면서
        // 가장 늦게 지는 날짜를 temp에 저장
        while (i < N && flowers[i].start <= curr) {
            temp = max(temp, flowers[i].end);
            i++;
        }

        // temp가 갱신되지 않았다는 것은
        // 현재 날짜 curr 이후로 구간을 확장할 수 있는 꽃이 없다는 의미 -> 빈 구간 발생
        if (temp == curr) {
            count = 0;
            break;
        }

        curr = temp;
        count++;
    }
    
    cout << count;
    
    return 0;
}