#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N, M;
	int farthest = 0;
	cin >> N >> M;

	vector<int> pos, neg;

	for (int i = 0; i < N; i++) {
		int book;
		cin >> book;

		if (book < 0) neg.emplace_back(-book);
		else pos.emplace_back(book);

		farthest = max(farthest, abs(book));
	}

	sort(all(pos), greater()); sort(all(neg), greater());

	int ans = 0;

	for (int i = 0; i < pos.size(); i += M) ans += pos[i];
	for (int i = 0; i < neg.size(); i += M) ans += neg[i];

	cout << (ans * 2 - farthest);
}
