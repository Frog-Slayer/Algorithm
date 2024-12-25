#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N, B;
	cin >> N >> B;

	vector<int> A(N);
	int idx;

	for (int i = 0; i < N; i++) {
		cin >> A[i];

		if (A[i] == B) idx = i;
	}

	map<int, int> m;

	int cnt = 1;

	for (int i = idx; i < N; i++) {
		if (A[i] > B) cnt++;
		else cnt--;
		
		m[cnt]++;
	}

	int ans = 0;

	cnt = 1;
	for (int i = idx; i >= 0; i--) {
		if (A[i] > B) cnt++;
		else cnt--;
		
		ans += m[-cnt];
	}

	cout << ans;


}