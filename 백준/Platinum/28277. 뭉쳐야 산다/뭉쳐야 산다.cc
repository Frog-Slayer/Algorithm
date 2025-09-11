#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;
vector<set<int>> s;

int main() { 
	fastio;

	int N, Q;
	cin >> N >> Q;

	s.resize(N + 1);
	for (int i = 1; i <= N; i++) { 
		int n;
		cin >> n;

		for (int j = 0; j < n; j++) { 
			int sij;
			cin >> sij;

			s[i].emplace(sij);
		}
	}

	for (int i = 0; i < Q; i++) { 
		int c;
		cin >> c;

		if (c == 1) { 
			int a, b;
			cin >> a >> b;

			if (s[a].size() < s[b].size()) swap(s[a], s[b]);

			s[a].merge(s[b]);
			s[b].clear();
		}
		else { 
			int a;
			cin >> a;

			cout << s[a].size() << '\n';
		}
	}
}
