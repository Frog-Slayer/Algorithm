#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_D = 10000;
const int INF = 99999;
int N, D;
int dist[MAX_D + 1];
vector<pair<pair<int, int>, int>> v; 

int main(){
	scanf("%d%d", &N, &D);

	for (int i = 0; i < N; i++){
		int s, e, d;
		scanf("%d%d%d", &s, &e, &d);
		v.push_back({{s, e}, d});
	}

	sort(v.begin(), v.end());

	int ans = INF;
	for (int i = 0; i < (1 << N); i++){
		int s = 0, e = 0, d = 0;
		int dist = 0;
		for (int j = 0; j < N; j++){
			if (!(i & (1 << j))) continue;
			s = v[j].first.first;
			if (s < e) {
				dist = INF;
				break;
			}
			dist += (s - e);//걸어감
			e = v[j].first.second; 
			d = v[j].second;
			dist += d;
		}
		if (e > D) continue;
		dist += D - e;
		ans = min(ans, dist);
	}

	printf("%d", ans);

}