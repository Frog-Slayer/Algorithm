#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

string lower_case(string s) { 
	string ret = s;

	for (char &c : ret) { 
		if (c >= 'A' && c <= 'Z') { 
			c -= 'A';
			c += 'a';
		}
	}

	return ret;
}

int main() { 
	fastio;

	while (true) { 
		int N;
		cin >> N;

		if (!N) break;

		vector<pair<string, int>> v(N);

		for (int i = 0; i < N; i++) cin >> v[i].first >> v[i].second;

		sort(all(v), [&](auto &p1, auto &p2) { 
				auto &[s, i] = p1;
				auto &[t, j] = p2;

				if (i == j) return lower_case(s) <= lower_case(t);
				return i >= j;
			});

		bool push_left = false;
		deque<string> deq;

		for (auto &[s, i] : v) { 
			if (push_left) deq.emplace_front(s);
			else deq.emplace_back(s);

			push_left = !push_left;
		}


		for (string &s : deq) cout << s << ' ';

		cout << '\n';
	}
}
