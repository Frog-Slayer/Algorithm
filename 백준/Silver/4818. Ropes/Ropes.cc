#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	while (true) { 
		int n;
		cin >> n;

		if (!n) break;

		vector<int> p(n);

		int sum = 0;

		for (int i = 0; i < n; i++) { 
			cin >> p[i];
			sum += p[i];
		}

		for (int j = 50; j < 80; j += 10) { 
			if (j < sum * 2) cout << 0 << ' ';
			else { 
				int minn = 2000;

				for (int i = 0; i < n; i++) { 
					minn = min(minn, j / p[i] + 1);
				}

				cout << max(2, minn) << ' ';
			}
		}

		cout << '\n';
	}


}
