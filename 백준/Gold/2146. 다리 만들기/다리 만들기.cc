#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 100;

int N;
int m[MAXN][MAXN];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void initDist(int dist[MAXN][MAXN]){
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) dist[i][j] = 1000000;
}

void log(int dist[MAXN][MAXN]){
    printf("===============================\n");
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}


int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            scanf("%d", &m[i][j]);
        }
    }

    //섬 만들기
    int islandIdx = 2;
    queue<pair<int, int>> q;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (m[i][j] != 1) continue;
            q.push({i, j});
            m[i][j] = islandIdx;

            while (!q.empty()){
                pair<int, int> front = q.front();
                int x = front.first, y = front.second;
                q.pop();
                
                for (int d = 0; d < 4; d++){
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue; 
                    if (m[nx][ny] != 1) continue;
                    m[nx][ny] = islandIdx;
                    q.push({nx, ny});
                }
            }
            islandIdx++;
        }
    }

    // log(m);

    //다리 이어보기
    int ans = 1000000;

    islandIdx = 2;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (m[i][j] != islandIdx) continue;
            int dist[MAXN][MAXN]; 
            initDist(dist);
            dist[i][j] = 0;
            q.push({i, j});
            
            while (!q.empty()){
                pair<int, int> front = q.front();
                int x = front.first, y = front.second;
                q.pop();
                
                for (int d = 0; d < 4; d++){
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue; 
                    if (m[nx][ny] == islandIdx && dist[nx][ny]) {
                        dist[nx][ny] = 0;
                        q.push({nx, ny});
                    }
                    else if (!m[nx][ny] && dist[nx][ny] > dist[x][y] + 1){
                        dist[nx][ny] = dist[x][y] + 1;
                        q.push({nx, ny});
                    } 
                    else if (m[nx][ny] && m[nx][ny] != islandIdx) {
                        ans = min(ans, dist[x][y]);
                    }
                }
            }

            // log(dist);
            islandIdx++;
        }
    }

    printf("%d", ans);
}