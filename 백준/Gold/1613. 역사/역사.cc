#include <iostream>
using namespace std;

const int MAXN = 401;
const int INF = 400 * 400;
int adj[MAXN][MAXN];

int main(){
	int n, k;
	scanf("%d%d", &n, &k);

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			adj[i][j] = INF;
		}
		adj[i][i] = 0;
	}

	for (int i = 0; i < k; i++){
		int before, after;
		scanf("%d%d", &before, &after);
		adj[before][after] = 1;
	}

	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);	
			}
		}
	}

	int s;
	scanf("%d", &s);

	for (int i = 0; i < s; i++){
		int before, after;
		scanf("%d%d", &before, &after);

		if (adj[before][after] != INF) printf("-1");
		else if (adj[after][before] != INF) printf("1");
		else printf("0");

		printf("\n");
	}


}