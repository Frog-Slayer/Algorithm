#include <iostream>
#include <vector>
using namespace std;

const int INF = 1024000000; 
int items[100];
int adj[100][100];

int main(){
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);

    for (int i = 0; i < n; i++){
        scanf("%d", &items[i]);
    }

    for (int i = 0; i < r; i++){
        int a, b, l;
        scanf("%d%d%d", &a, &b, &l);
        a--, b--;
        adj[a][b] = adj[b][a] = l;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j) adj[i][j] = 0;
            else if (!adj[i][j]) adj[i][j] = INF;
        }
    }

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++){
        int sum = 0; 
        for (int j = 0; j < n; j++){
            if (adj[i][j] <= m) sum += items[j];
        }

        ans = max(ans, sum);
    }

    printf("%d", ans);
}