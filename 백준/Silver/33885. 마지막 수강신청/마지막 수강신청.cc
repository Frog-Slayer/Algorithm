#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main () { 
	fastio;

	int N, M;
	cin >> N >> M;

	map<string, int> days;
	days.emplace("MON", 1);
	days.emplace("TUE", 2);
	days.emplace("WED", 3);
	days.emplace("THU", 4);
	days.emplace("FRI", 5);

	vector<tuple<int, vector<pair<int, int>>>> v;


	for (int i = 0; i < N; i++) { 
		int c, s;
		cin >> c >> s;

		vector<pair<int, int>> u;

		for (int j = 0; j < s; j++) { 
			int h;
			string d;
			cin >> d >> h;
			
			u.emplace_back(days[d], h);
		}

		v.emplace_back(c, u);
	}

	bool ans = false;

	for (int i = 0; i < (1 << N); i++) { 
		bool possible = true;
		int sum = 0;
		set<pair<int, int>> s;

		for (int bit = 0; bit < N; bit++) { 
			if (i & (1 << bit)) { 
				auto &[c, u] = v[bit];

				for (auto &[d, h] : u) { 
					if (s.find({d, h}) != s.end()) { 
						possible = false;
						break;
					}
					s.emplace(d, h);
				}

				sum += c;
			}
		}

		if (possible && sum >= M) { 
			ans = true;
			break;
		}
	}

	cout << (ans ? "YES" : "NO");
}
