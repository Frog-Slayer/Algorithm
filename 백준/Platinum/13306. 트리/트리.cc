#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

vector<int> parent, group;

int find(int a) { 
	if (group[a] == a) return a;
	return group[a] = find(group[a]);
}

void merge(int a, int b) { 
	a = find(a), b = find(b);

	if (a == b) return;
	group[a] = b;
}

int main() { 
	fastio;

	int N, Q;
	cin >> N >> Q;

	parent.resize(N + 1);
	group.resize(N + 1);

	for (int i = 2; i <= N; i++) cin >> parent[i];
	for (int i = 1; i <= N; i++) group[i] = i;

	vector<tuple<int, int, int>> queries;

	for (int i = 0; i < N - 1 + Q; i++) { 
		int x;
		cin >> x;

		if (!x) { 
			int b;
			cin >> b;
			queries.emplace_back(x, b, 0);
		}
		else { 
			int c, d;
			cin >> c >> d;
			queries.emplace_back(x, c, d);
		}
	}

	vector<bool> ans;

	for (int i = N + Q - 2; i >= 0; i--) { 
		auto [x, a, b] = queries[i];

		if (x) ans.emplace_back(find(a) == find(b));
		else merge(a, parent[a]);
	}

	for (int i = Q - 1; i >= 0; i--) { 
		cout << (ans[i] ? "YES\n" : "NO\n");
	}


}
