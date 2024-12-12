#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int to_int(char c) {
	if (c == '0') return 0;
	if ('a' <= c && c <= 'z') return c - 'a' + 1;
	return c - 'A' + 27;
}

vector<int> parent;

int find(int a) {
	if (parent[a] == a) return a;
	return parent[a] = find(parent[a]);
}

bool merge(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	parent[a] = b;
	return true;
}

int main() {
	fastio;

	int N;
	cin >> N;

	vector<tuple<int, int, int>> v;
	parent.resize(N + 1);

	for (int i = 1; i <= N; i++){
		parent[i] = i;
		int W;
		cin >> W;
		v.emplace_back(W, 0, i);
	}


	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int p;
			cin >> p;
			if (i > j) v.emplace_back(p, i, j);
		}
	}

	sort(all(v));

	int sum = 0;

	for (auto &[p, i, j] : v) {
		if (merge(i, j)) sum += p;
	}

	cout << sum;

}