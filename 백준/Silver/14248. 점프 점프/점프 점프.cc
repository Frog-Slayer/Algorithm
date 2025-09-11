#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;

	int N;
	cin >> N;

	vector<int> a(N);
	vector<bool> visited(N);

	for (int i = 0; i < N; i++) cin >> a[i];

	int s;
	cin >> s;

	queue<int> q;
	visited[--s] = true;
	q.emplace(s);

	int ans = 1;

	while (!q.empty()) { 
		int cur = q.front();
		q.pop();

		int left = cur - a[cur], right = cur + a[cur];

		if (left >= 0 && !visited[left]) { 
			visited[left] = true;
			ans++;
			q.emplace(left);
		}

		if (right < N && !visited[right]) { 
			visited[right] = true;
			ans++;
			q.emplace(right);
		}
	}

	cout << ans;
}
