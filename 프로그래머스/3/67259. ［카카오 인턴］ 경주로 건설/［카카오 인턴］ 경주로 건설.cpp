#include <bits/stdc++.h>
using namespace std;

#define Coord pair<int,int>
#define X first
#define Y second

enum Direction { UP=0, LEFT=1, RIGHT=2, DOWN=3, INIT=-1 };
const int WALL=1;
const int INF=25*25*500;
const vector<Coord> dr={{-1,0},{0,-1},{0,1},{1,0}};

struct Node {
    int x, y, cost;
    Direction dir;
};

bool isOut(int N,int x,int y){return x<0||x>=N||y<0||y>=N;}
bool isStraight(Direction d1, Direction d2){ return d1==INIT || d1==d2; }

int getCost(Direction d1, Direction d2){
    return isStraight(d1,d2)?100:600;
}

int solution(vector<vector<int>> board){
    int N=board.size();
    vector<vector<vector<int>>> cost(N, vector<vector<int>>(N, vector<int>(4, INF)));
    queue<Node> q;

    q.push({0,0,0,INIT});
    for(int i=0;i<4;i++) cost[0][0][i]=0;

    while(!q.empty()){
        auto [x,y,c,d]=q.front(); q.pop();
        for(int i=0;i<4;i++){
            int nx=x+dr[i].X, ny=y+dr[i].Y;
            if(isOut(N,nx,ny)||board[nx][ny]==WALL) continue;
            int ncost=c+getCost(d,(Direction)i);
            if(cost[nx][ny][i]>ncost){
                cost[nx][ny][i]=ncost;
                q.push({nx,ny,ncost,(Direction)i});
            }
        }
    }

    return *min_element(cost[N-1][N-1].begin(), cost[N-1][N-1].end());
}
