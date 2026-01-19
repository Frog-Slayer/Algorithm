#include <iostream>
#include <queue>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int T;
	cin >> T;

	for (int tt = 1; tt <= T; tt++) { 
		int t;
		cin >> t;

		vector<pair<char, int>> move;
		queue<int> orange, blue;

		for (int i = 0; i < t; i++) { 
			char color;
			int button;

			cin >> color >> button;

			move.emplace_back(color, button);
			
			if (color == 'O') orange.emplace(button);
			else blue.emplace(button);
		}

		int ocur = 1, bcur = 1;
		int ans = 0;


		for (auto [color, button] : move) { 
			while (true) { 
				bool opressed = false, bpressed = false;

				if (color == 'O' && button == ocur) { 
					orange.pop();
					opressed = true;
				}
				else if (color == 'B' && button == bcur) { 
					blue.pop();
					bpressed = true;
				}

				if (!opressed && !orange.empty()) { 
					int next = orange.front();
					if (ocur < next) ocur++;
					else if (ocur > next) ocur--;
				}
				
				if (!bpressed && !blue.empty()) { 
					int next = blue.front();
					if (bcur < next) bcur++;
					else if (bcur > next) bcur--;
				}

				ans++;

				if (bpressed || opressed) break;
			}
		}

		cout << "Case #" << tt << ": " << ans << '\n';

	}

}
