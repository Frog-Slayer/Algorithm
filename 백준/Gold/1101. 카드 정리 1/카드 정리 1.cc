#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int N, M;
	cin >> N >> M;

	int ans = 0;
	bool set_joker = false;

	vector<bool> has_one(M + 1);

	for (int i = 0; i < N; i++) { 
		int cnt = 0, color = 0;
		int prev_ans = ans;

		for (int j = 0; j < M; j++) { 
			int c;
			cin >> c;
			if (c) { 
				color = j + 1;
				cnt++;
			}
		}

		if (!cnt) continue;
		else if (cnt == 1) { 
			if (has_one[color]){ 
				if (!set_joker) set_joker = true;
				else ans++; 
			}
			has_one[color] = true;
		}
		else { 
			if (!set_joker) set_joker = true;
			else ans++;
		}
	}

	cout << ans;

}