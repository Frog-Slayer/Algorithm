#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;
int N;
vector<pair<int, int>> v;
vector<int> xx, yy;
int ans[50];

int manhattan(pair<int, int> a, pair<int, int> b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int main(){
	scanf("%d", &N);

	for (int x, y, i = 0; i < N; i++) {
		scanf("%d%d", &x, &y);
		v.emplace_back(x, y);
		xx.emplace_back(x);
		yy.emplace_back(y);
	}
	
	for (int i = 1; i < N; i++) ans[i] = INF;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			vector<int> dist;
			for (int k = 0; k < N; k++) dist.emplace_back(manhattan({xx[i], yy[j]}, v[k]));

			sort(dist.begin(), dist.end());

			for (int k = 1; k < N; k++){
				dist[k] += dist[k - 1]; 
				ans[k] = min(ans[k], dist[k]);
			}
		}
	}

	for (int i = 0; i < N; i++) printf("%d ", ans[i]);
}
