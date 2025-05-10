#include <iostream>
#include <unordered_set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	unordered_set<string> s;

	int N, M;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;

		s.emplace(str);
	}

	int ans = 0;

	for (int i = 0; i < M; i++){
		string str;
		cin >> str;

		ans += s.count(str);
	}

	cout << ans;
}
