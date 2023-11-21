#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 10001;
int N, M;
int A, B;
int conCnt[MAXN];
vector<vector<int>> adj;

int bfs(int start){
    bool visited[MAXN + 1] = {false, } ;
    int ret = 1;

    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()){
        int front = q.front();
        q.pop();

        for (int next : adj[front]){
            if (visited[next]) continue;
            visited[next] = true;
            ret++;
            q.push(next);
        }
    }

    return ret;
}

int main(){
    //단방향 그래프가 주어졌을 때 
    scanf("%d%d", &N, &M);
    adj.resize(N + 1);

    for (int i = 0; i < M; i++){
        scanf("%d%d", &A, &B);
        adj[B].push_back(A);
    }

    int maxConnection = 0;

    for (int i = 1; i <= N; i++) {
        conCnt[i] = bfs(i);
        maxConnection = max(maxConnection, conCnt[i]);
    }

    for (int i = 1; i <= N; i++) {
        if (conCnt[i] == maxConnection) printf("%d ", i);
    }

}