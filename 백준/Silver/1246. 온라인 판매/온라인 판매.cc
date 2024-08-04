#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> eggs;

int main() {
	scanf("%d%d", &N, &M);

	eggs.resize(M);

	for (int i = 0; i < M; i++) scanf("%d", &eggs[i]);

	sort(eggs.begin(), eggs.end());

	int price = 0;
	int ans = 0 ;

	for (int i = 0; i < M; i++) {
		int t = eggs[i] * min(N, M - i);
		if (t > ans) {
			ans = t;
			price = eggs[i];
		}
	}


	printf("%d %d", price, ans);
}
