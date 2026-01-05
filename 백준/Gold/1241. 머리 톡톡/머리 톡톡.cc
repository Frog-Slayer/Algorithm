#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int MAX_N = 1000000;

int cnt[MAX_N + 1];
unordered_map<int, int> m;

void set_cnt() { 
	for (int i = 1; i <= MAX_N; i++) { 
		int c = m[i];
		if (!c) continue;
		for (int j = i; j <= MAX_N; j += i) { 
			cnt[j] += c;
		}
	}
}

int main() { 
	fastio;

	int N;
	cin >> N;

	vector<int> num(N + 1);

	for (int i = 1; i <= N; i++) { 
		int n;
		cin >> n;
		num[i] = n;
		m[n]++;
	}

	set_cnt();

	for (int i = 1; i <= N; i++) { 
		cout << cnt[num[i]] - 1 << '\n';
	}
}
