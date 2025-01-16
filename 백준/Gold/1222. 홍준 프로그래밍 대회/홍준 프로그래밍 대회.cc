#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int MAX = 2000001;

int main() {
	fastio;

	int N;
	cin >> N;

	vector<int> students(2000001);

	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		students[n]++;
	}

	long long ans = 0;

	for (int i = 1; i < MAX; i++) {
		long long cnt = 0;

		for (int j = 1; i * j < MAX; j++) cnt += students[i * j];

		if (cnt >= 2) ans = max(ans, cnt * i);
	}

	

	cout << ans;
	
}