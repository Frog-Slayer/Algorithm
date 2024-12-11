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

	int sum = 0, mst = 0, cnt = 0;

	vector<tuple<int, int, int>> v;
	parent.resize(N);

	for (int i = 0; i < N; i++) {
		parent[i] = i;
		string s;
		cin >> s;

		for (int j = 0; j < N; j++) {
			int tmp = to_int(s[j]);
			if (tmp) {
				sum += tmp;
				v.emplace_back(tmp, i, j);
			}
		}
	}

	sort(all(v));

	for (auto &[w, i, j] : v) {
		if (merge(i, j)){
			mst += w;
			cnt++;
		}
	}

	cout << (cnt == N - 1 ? sum - mst : -1); 

}