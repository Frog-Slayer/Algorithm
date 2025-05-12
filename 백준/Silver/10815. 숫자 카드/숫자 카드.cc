#include <iostream>
#include <unordered_set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	unordered_set<int> s;
	int N, M;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		s.emplace(n);
	}

	cin >> M;

	for (int i = 0; i < M; i++) {
		int m;
		cin >> m;
	
		cout << s.count(m) << ' ';
	}
}
