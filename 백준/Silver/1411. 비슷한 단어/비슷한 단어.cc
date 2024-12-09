#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

bool is_similar(string a, string b) {
	map<char, char> atob, btoa;

	for (int i = 0; a[i]; i++) {
		if (atob.find(a[i]) == atob.end()){
			atob[a[i]] = b[i];
			if (btoa.find(b[i]) == btoa.end()) btoa[b[i]] = a[i];
			if (btoa[b[i]] != a[i]) return false;
		}
		if (atob[a[i]] != b[i]) return false;
	}

	return true;
}

int main() {
	fastio;

	int N;
	cin >> N;

	vector<string> v(N);

	for (int i = 0; i < N; i++) cin >> v[i];

	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (is_similar(v[i], v[j])) ans++;
		}
	}

	cout << ans;
}