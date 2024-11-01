#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int parse(string s) {
	int ret = 0;

	for (int i = 0; s[i]; i++) {
		if (s[i] == '.') continue;
		ret *= 10;
		ret += s[i] - '0';
	}

	return ret;
}

int N;
vector<int> v;

int solve() {
	for (int i = 1; i <= 1000; i++) {
		bool is_ans = true;
		for (int j = 0; j < N; j++) {
			bool flag = false;

			for (int k = 0; k <= i * 10000; k += 1000) {
				if (v[j] == k / i) {
					flag = true;
					break;
				}
			}

			if (!flag) {
				is_ans = false;
				break;
			}
		}

		if (is_ans) return i;
	}

	return 0;
}

int main() {
	fastio;
	
	cin >> N;
	
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		v.emplace_back(parse(s));
	}

	cout << solve();
}