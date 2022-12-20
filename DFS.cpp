#include <stack>
#include <iostream>
#include <cstdio>
using namespace std;

int N = 10; 
int M = 10;

char field[10][10] = {'w','w','w','w','w','w','w','.','.','.',
                      '.','.','.','.','.','.','w','.','.','w',
                      '.','w','.','.','.','w','w','w','.','w',
                      '.','w','.','.','.','.','.','.','.','.',
                      'w','w','.','w','w','.','.','w','w','w',
                      '.','.','.','.','w','.','.','.','.','w',
                      '.','w','w','w','w','.','.','w','.','w',
                      '.','.','.','.','w','.','.','.','.','.',
                      '.','.','.','.','w','.','w','w','.','.',
                      '.','.','.','.','w','.','.','.','.','w'};


// DFS
void dfs(int x, int y){
    field[x][y] = '.';
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            int nx = x + dx, ny = y + dy;
            if (0 <= nx && nx < N && 0 <= ny && ny < M && field[nx][ny] == 'w') dfs(nx, ny);
        }
    }
    return;
}

int main(){
    // for (auto &row : field)
    // {
    //     for (auto &column : row)
    //     {
    //         std::cout << column << " ";
    //     }
    //     std::cout << std::endl;
    // }
    int res = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (field[i][j]== 'w'){
                dfs(i, j);
                res++;
            }
        }
    }
    printf("%d\n",res);
}