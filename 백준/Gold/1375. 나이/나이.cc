#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

int N, M;
unordered_map<string, int> nameMap;
vector<vector<int>> adj;
int idx;

int bfs(int a, int b){
    vector<bool> visited(N + 1, false);
    queue<int> q;

    q.push(a);
    visited[a] = true;

    while (!q.empty()){
        int front = q.front();
        q.pop();

        for (int next : adj[front]){
            if (next == b) return 1;
            if (visited[next]) continue;
            visited[next] = true;
            q.push(next);
        }
    }

    for (int i = 0; i <= N; i++) visited[i] = false; 
    q.push(b);
    visited[b] = true;

    while (!q.empty()){
        int front = q.front();
        q.pop();

        for (int next : adj[front]){
            if (next == a) return 2;
            if (visited[next]) continue;
            visited[next] = true;
            q.push(next);
        }
    }

    return 0;

}

int main(){
    scanf("%d%d", &N, &M);

    adj.resize(N + 1);
    for (int i = 0; i < M; i++){
        char name1[7], name2[7];
        int name1Idx, name2Idx;
        scanf("%s %s", name1, name2);

        if (!nameMap[name1]) nameMap[name1] = name1Idx = ++idx;
        else name1Idx = nameMap[name1];

        if (!nameMap[name2]) nameMap[name2] = name2Idx = ++idx;
        else name2Idx = nameMap[name2];

        adj[name1Idx].push_back(name2Idx);
    }

    int Q;
    scanf("%d", &Q);

    for (int i = 0; i < Q; i++){
        char name1[7], name2[7];
        int name1Idx, name2Idx;
        scanf("%s %s", name1, name2);

        name1Idx = nameMap[name1];
        name2Idx = nameMap[name2];

        if (!name1Idx || !name2Idx) printf("gg ");
        else {
            int ret = bfs(name1Idx, name2Idx);
            if (ret == 1) printf("%s ", name1);
            else if (ret == 2) printf("%s ", name2);
            else printf("gg ");
        }
    }
}