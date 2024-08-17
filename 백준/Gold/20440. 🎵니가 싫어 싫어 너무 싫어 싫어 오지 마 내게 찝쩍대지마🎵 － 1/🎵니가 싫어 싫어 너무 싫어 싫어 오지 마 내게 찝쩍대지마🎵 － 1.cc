#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int>> t;
vector<int> tt;
vector<int> acc;

int main() {
	int N;
	scanf("%d", &N);
	acc.resize(N * 2);

	for (int i = 0; i < N; i++) {
		int s, e;
		scanf("%d%d", &s, &e);
		t.emplace_back(s, e);
		tt.emplace_back(s);
		tt.emplace_back(e);
	}

	sort(tt.begin(), tt.end());
	tt.erase(unique(tt.begin(), tt.end()), tt.end());

	for (int i = 0; i < N; i++) {
		int s = lower_bound(tt.begin(), tt.end(), t[i].first) - tt.begin();
		int e = lower_bound(tt.begin(), tt.end(), t[i].second) - tt.begin();

		acc[s] += 1;
		acc[e] -= 1;
	}

	int ans = 0, s = 0, e = 0;
	bool cont = false;

	for (int i = 0; i < 2 * N; i++) {
		if (i) acc[i] += acc[i - 1];

		if (ans < acc[i]) {
			ans = acc[i];
			s = i;
			cont = true;
		}
		else if (ans > acc[i]) cont = false;

		if (cont) e = i + 1;
	}

	printf("%d\n%d %d", ans, tt[s], tt[e]);
}