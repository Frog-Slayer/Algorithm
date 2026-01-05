#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int MAX_N = 1000000;

int cnt[MAX_N + 1];
int freq[MAX_N + 1];

void set_cnt() { 
	for (int i = 1; i <= MAX_N; i++) { 
		int c = freq[i];
		if (!c) continue;
		for (int j = i; j <= MAX_N; j += i) { 
			if (!freq[j]) continue;
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
		cin >> num[i];
		freq[num[i]]++;
	}

	set_cnt();

	for (int i = 1; i <= N; i++) { 
		cout << cnt[num[i]] - 1 << '\n';
	}
}