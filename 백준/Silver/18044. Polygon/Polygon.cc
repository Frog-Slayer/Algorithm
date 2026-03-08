#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main () { 
	fastio;

	int T;
	cin >> T;

	while (T--) { 
		int N;
		cin >> N;

		vector<ll> lengths(N);

		for (int i = 0; i < N; i++) cin >> lengths[i];

		sort(all(lengths));

		for (int i = 1; i < N; i++) lengths[i] += lengths[i - 1];

		bool has_answer = false;

		for (int i = N - 1; i > 0; i--) { 
			ll longest = lengths[i] - lengths[i - 1];
			if (longest < lengths[i - 1]) { 
				cout << lengths[i] << '\n';
				has_answer = true;
				break;
			}
		}

		if (!has_answer) cout << "0\n";
	}
}
