#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;
	
	int n, m;
	cin >> n >> m;

	set<int> s;

	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;

		s.emplace(a);
	}

	for (int i = 0; i < m; i++){
		int b;
		cin >> b;

		if (s.count(b)) s.erase(b);
	}


	cout << s.size() << '\n';
	for (auto i : s) cout << i << ' ';
}
