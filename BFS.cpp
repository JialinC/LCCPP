#include <queue>
#include <iostream>
#include <cstdio>
#include <utility>
using namespace std;

const int INF = 100000000;
int N = 10; 
int M = 10;
typedef pair<int, int> P;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int sx=0, sy=1;
int gx=9, gy=8;

char maze[10][10] = {'#','S','#','#','#','#','#','#','.','#',
                     '.','.','.','.','.','.','#','.','.','#',
                     '.','#','.','#','#','.','#','#','.','#',
                     '.','#','.','.','.','.','.','.','.','.',
                     '#','#','.','#','#','.','#','#','#','#',
                     '.','.','.','.','#','.','.','.','.','#',
                     '.','#','#','#','#','#','#','#','.','#',
                     '.','.','.','.','#','.','.','.','.','.',
                     '.','#','#','#','#','.','#','#','#','.',
                     '.','.','.','.','#','.','.','.','G' ,'#'};

int d[10][10];

// BFS
int bfs(){
    queue<P> que;
    for (int i = 0; i < N; i++)
        for(int j = 0; j < M; j++) d[i][j] = INF;
    que.push(P(sx, sy));
    d[sx][sy] = 0;

    while (que.size()){
        P p = que.front();
        que.pop();
        if (p.first == gx && p.second == gy) break;

        for (int i = 0; i < 4; i++){
            int nx = p.first + dx[i], ny =  p.second + dy[i];
            if (0 <= nx && nx < N && 0 <= ny && ny < M && maze[nx][ny] != '#' && d[nx][ny] == INF){
                que.push(P(nx, ny));
                d[nx][ny] = d[p.first][p.second]+1;
            }
        }
    }
    return d[gx][gy];
}

int main(){
    int res = bfs();
    printf("%d\n",res);
}