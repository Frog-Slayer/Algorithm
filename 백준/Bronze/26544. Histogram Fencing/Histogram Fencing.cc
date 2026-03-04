#include <iostream>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main () { 
	fastio;

	int T;
	cin >> T;

	while (T--) { 
		int N;
		cin >> N;

		int sum = 0;

		for (int i = 0; i < N; i++) { 
			int w;
			cin >> w;
			sum += w;
		}

		sum *= 2;
		int prev_h = 0;

		for (int i = 0; i < N; i++) { 
			int h;
			cin >> h;

			sum += abs(h - prev_h);
			prev_h = h;

			if (i == N - 1) sum += h;
		}

		cout << sum << '\n';
	}

}
