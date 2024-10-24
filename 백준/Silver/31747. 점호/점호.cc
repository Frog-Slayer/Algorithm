#include <iostream>
#include <queue>

using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N, K;
	cin >> N >> K;

	queue<int> one, two;

	for (int i = 0; i < N; i++) {
		int A;
		cin >> A;
		if (A == 1) one.push(i);
		else two.push(i);
	}

	int cur = 0, ans = 0;

	while (!one.empty() || !two.empty()) {
		if (one.empty() && two.empty()) break;

		bool o = !one.empty() && one.front() < cur + K;
		bool t = !two.empty() && two.front() < cur + K;  

		if (o && t) {
			cur += 2;
			one.pop();
			two.pop();
		}
		else if (o) {
			cur++;
			one.pop();
		}
		else if (t){
			cur++;
			two.pop();
		}
		
		ans++;
	}

	cout << ans;




}