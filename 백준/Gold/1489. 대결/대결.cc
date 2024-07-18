#include <iostream>
#include <algorithm>
using namespace std;

int N;
vector<int> a, b;

int main(){
	scanf("%d", &N);
	a.resize(N), b.resize(N);

	for (int i = 0; i < N; i++) scanf("%d", &a[i]);
	for (int i = 0; i < N; i++) scanf("%d", &b[i]);

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	int ans = 0;

	for (int i = 0; i < N; i++) {
		int cur = a[i];	
		int lb = lower_bound(b.begin(), b.end(), cur) - b.begin();
		if (lb) {
			b.erase(b.begin() + lb - 1);
			a[i] = 0;
			ans += 2;
		}
	}

	int idx = 0;
	for (int i = 0; i < N; i++) {
		for (int j = idx; j < b.size(); j++) {
			if (a[i] == b[j]) {
				ans += 1;
				idx = j + 1;
				break;
			}
		}
	}

	printf("%d", ans);
}