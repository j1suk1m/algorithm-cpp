#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Music {
    int number;
    int play;
    
    Music(int number, int play) {
        this->number = number;
        this->play = play;
    }
};

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    map<string, int> genreToPlay;
    map<string, vector<Music>> genreToMusics;
    int musicCount = genres.size();
    
    // 맵에 <장르, 총 재생 횟수> 저장
    // 맵에 <장르, 음악들> 저장
    for (int i = 0; i < musicCount; i++) {
        string genre = genres[i];
        int play = plays[i];
        genreToPlay[genre] += play;
        genreToMusics[genre].push_back(Music(i, play));
    }
    
    vector<pair<string, int>> sortedGenreToPlay(genreToPlay.begin(), genreToPlay.end());
    
    // 총 재생 횟수가 많은 순으로 장르 정렬
    sort(sortedGenreToPlay.begin(), sortedGenreToPlay.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    
    // 장르별 음악 정렬
    // 재생 횟수가 많은 순, 고유 번호가 작은 순
    for(auto& p : genreToMusics) {
        sort(p.second.begin(), p.second.end(), [](const Music &a, const Music &b) {
            if (a.play != b.play) return a.play > b.play; // 재생 횟수 내림차순
            return a.number < b.number; // 고유 번호 오름차순
        });
    }
    
    for (int i = 0; i < sortedGenreToPlay.size(); i++) {
        string genre = sortedGenreToPlay[i].first;
        
        for (int j = 0; j < min((int)genreToMusics[genre].size(), 2); j++) {
            answer.push_back(genreToMusics[genre][j].number);
        }
    }
    
    return answer;
}