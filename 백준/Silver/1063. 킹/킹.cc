#include <iostream>
using namespace std;

pair<int, int> kingPos, stonePos;

int main(){
    char s1[3], s2[3];
    int mvCount;

    scanf("%s %s %d", s1, s2, &mvCount);

    kingPos = {s1[0] - 'A', s1[1] - '1'};
    stonePos = {s2[0] - 'A', s2[1] - '1'};

    char cmd[3];

    for (int i = 0; i < mvCount; i++){
        scanf("%s", cmd);
        int x = 0, y = 0;

        for (int i = 0; cmd[i]; i++){
            switch (cmd[i]){
                case 'R': x++; break; 
                case 'L': x--; break;
                case 'B': y--; break; 
                case 'T': y++; break;
                default : break;
            }
        }

        int nx = kingPos.first + x, ny = kingPos.second + y;
        if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) continue;

        if (nx == stonePos.first && ny == stonePos.second){
            int nextStoneX = stonePos.first + x, nextStoneY = stonePos.second + y;
            if (nextStoneX < 0 || nextStoneX  >= 8 || nextStoneY < 0 || nextStoneY >= 8) continue;
            stonePos = {nextStoneX, nextStoneY};
        }

        kingPos = {nx, ny};
    }

    printf("%c%d\n%c%d\n", kingPos.first + 'A', kingPos.second + 1, stonePos.first + 'A', stonePos.second + 1);
}