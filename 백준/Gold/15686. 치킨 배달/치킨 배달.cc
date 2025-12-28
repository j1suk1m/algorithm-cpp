#define X first
#define Y second
#define Coord pair<int, int>

#include <iostream> // cin, cout
#include <vector> // vector
#include <utility> // pair
#include <algorithm> // min
#include <cstdlib> // abs

using namespace std;

const int HOUSE = 1;
const int CHICKEN_PLACE = 2;

int N, M;
int answer = 100 * 50 * 2; // 도시의 치킨 거리

vector<vector<int>> city;
vector<vector<int>> manhattanDistances; // 집과 치킨집 사이의 맨해튼 거리
vector<Coord> chickenPlaces; // 치킨집 좌표
vector<Coord> houses; // 집 좌표
vector<int> selectedChickenPlaceIndices; // 현재까지 선택된 치킨집 좌표 인덱스

// 프로토타입
int calculateCityChickenDistance();
void selectChickenPlaces(int);

int main() {
    cin >> N >> M;

    // [1] 도시 저장
    for (int x = 0; x < N; x++) {
        city.push_back(vector<int>());
        
        for (int y = 0; y < N; y++) {
            int curr;
            cin >> curr;
            city[x].push_back(curr);

            // 특수 좌표 저장
            if (curr == HOUSE) {
                houses.push_back(make_pair(x, y));
            } else if (curr == CHICKEN_PLACE) {
                chickenPlaces.push_back(make_pair(x, y));
            }
        }
    }

    int housesCount = (int)houses.size();
    int chickenPlacesCount = (int)chickenPlaces.size();
    
    manhattanDistances.resize(housesCount, vector<int>(chickenPlacesCount));
    
    // [2] 치킨집까지의 맨해튼 거리 계산
    for (int i = 0; i < housesCount; i++) {
        Coord house = houses[i];
        
        for (int j = 0; j < chickenPlacesCount; j++) {
            Coord chickenPlace = chickenPlaces[j];
            
            int xDifference = abs(house.X - chickenPlace.X);
            int yDifference = abs(house.Y - chickenPlace.Y);
            int manhattanDistance = xDifference + yDifference;
            manhattanDistances[i][j] = manhattanDistance;
        }
    }

    // [3] M개의 치킨집 선택 후 도시의 치킨 거리 계산
    selectChickenPlaces(0);

    // [4] 도시의 치킨 거리 출력
    cout << answer;
    
    return 0;
}

// 도시의 치킨 거리 계산
int calculateCityChickenDistance() {
    int cityChickenDistance = 0;
    int housesCount = (int)houses.size();

    for (int i = 0; i < housesCount; i++) {
        int chickenDistance = 50 * 2;

        // 치킨 거리 계산
        for (const int j : selectedChickenPlaceIndices) {
            int manhattanDistance = manhattanDistances[i][j];
            chickenDistance = min(chickenDistance, manhattanDistance);
        }

        // 도시의 치킨 거리에 누적
        cityChickenDistance += chickenDistance;
    }

    return cityChickenDistance;
}

// 폐업시키지 않을 M개의 치킨집 선택
void selectChickenPlaces(int start) {
    int selectedChickenPlacesCount = (int)selectedChickenPlaceIndices.size();

    // 치킨집을 모두 선택한 경우
    if (selectedChickenPlacesCount == M) {
        // 현재 조합에 대해 도시의 치킨 거리를 계산한 뒤 최솟값 갱신
        int cityChickenDistance = calculateCityChickenDistance();
        answer = min(answer, cityChickenDistance);
        return;    
    }

    for (int i = start; i < (int)chickenPlaces.size(); i++) {
        selectedChickenPlaceIndices.push_back(i);
        selectChickenPlaces(i + 1);
        selectedChickenPlaceIndices.pop_back();
    }
}