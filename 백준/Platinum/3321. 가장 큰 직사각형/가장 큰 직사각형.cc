#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 15000, MAX_M = 1500;

int N, M, ans;
char buffer[MAX_M + 1];
int cnt[MAX_M];
vector<int> v;

int main(){ 
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N; i++){ 
		scanf("%s", buffer);

		vector<int> tmp;

		for (int i = 0; i < v.size(); i++) {
			int idx = v[i];
			if (buffer[idx] == '0') cnt[idx] = 0;
			else cnt[idx]++, tmp.emplace_back(idx);
		}

		for (int i = 0; i < M; i++) {
			if (cnt[i] == 0 && buffer[i] == '1') cnt[i]++, tmp.emplace_back(i); 
		}

		for (int i = 0; i < tmp.size(); i++) {
			ans = max(ans, (i + 1) * (cnt[tmp[i]]));
		}
		
		v = tmp;
	}

	printf("%d", ans);
}