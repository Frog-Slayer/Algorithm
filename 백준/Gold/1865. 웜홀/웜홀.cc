#include <iostream>
#include <map>
using namespace std;

const int MAXN = 500;
const int INF = 1011111111;

int TC, N, M, W;
int S, E, T;
map<pair<int, int>, int> edges;
int dist[MAXN + 2];

bool bellman(int start){
    for (int i = 0; i <= N; i++){
        dist[i] = INF;
    }
    dist[start] = 0;

    for (int i = 0; i < N + 1; i++) {
        for (auto edge :edges){
            int from = edge.first.first;
            int to = edge.first.second;
            int cost = edge.second;

            if (dist[from] != INF && dist[from] + cost < dist[to]){
                if (i == N) {
                    return true; 
                }
                dist[to] = dist[from] + cost;
            }
        }
    }
    return false;
}

void push(int S, int E, int T){
    pair<int, int> sePair = make_pair(S, E);
    if (edges.find(sePair) == edges.end()) {
        edges.insert({sePair, T}); 
    }
    else {
        edges[sePair] = min(T, edges[sePair]);
    }
}


int main(){
    scanf("%d", &TC);
    while (TC--){
        scanf("%d%d%d", &N, &M, &W);
        edges.clear();

        for (int i = 0; i < M; i++){
            scanf("%d%d%d", &S, &E, &T);
            push(S, E, T);
            push(E, S, T);
        }

        for (int i = 0; i < W; i++){
            scanf("%d%d%d", &S, &E, &T);
            push(S, E, -T);
        }

        for (int i = 1; i <= N; i++) {
            push(0, i, 0);
        }

        bool found = bellman(0);

        if (found) printf("YES\n");
        else printf("NO\n");
    }
}