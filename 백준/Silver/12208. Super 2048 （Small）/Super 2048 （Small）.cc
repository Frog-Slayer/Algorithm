#include <iostream>
#include <queue>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) { 
		int n;
		string dir;

		cin >> n >> dir;

		vector<vector<int>> board(n, vector<int>(n));

		for (int i = 0; i < n; i++) { 
			for (int j = 0; j < n; j++) { 
				cin >> board[i][j];
			}
		}

		if (dir == "right" || dir == "left") { 
			int start = (dir == "right" ? n - 1 : 0);
			int d = (dir == "right" ? -1 : 1);

			for (int i = 0; i < n; i++) { 
				for (int j = start; j >= 0 && j < n; j += d) { 
					if (board[i][j] == 0) { 
						for (int next = j + d; next >= 0 && next < n; next += d) { 
							if (board[i][next]) { 
								board[i][j] = board[i][next];
								board[i][next] = 0;
								break;
							}
						}
					} 					
					for (int next = j + d; next >= 0 && next < n; next += d) { 
						if (!board[i][next]) continue;
						if (board[i][next] == board[i][j]) { 
							board[i][j] += board[i][next];
							board[i][next] = 0;
							break;
						}
						break;
					}
				}
			}
		}
		else { 
			int start = (dir == "down" ? n - 1 : 0);
			int d = (dir == "down" ? -1 : 1);

			for (int i = 0; i < n; i++) { 
				for (int j = start; j >= 0 && j < n; j += d) { 
					if (board[j][i] == 0) { 
						for (int next = j + d; next >= 0 && next < n; next += d) { 
							if (board[next][i]) { 
								board[j][i] = board[next][i];
								board[next][i] = 0;
								break;
							}
						}
					} 					

					for (int next = j + d; next >= 0 && next < n; next += d) { 
						if (!board[next][i]) continue;
						if (board[next][i] == board[j][i]) { 
							board[j][i] += board[next][i];
							board[next][i] = 0;
							break;
						}
						break;
					}
				}
			}
		}

		cout << "Case #" << t << ":\n";

		for (int i = 0; i < n; i++) { 
			for (int j = 0; j < n; j++) cout << board[i][j] << ' ';
			cout << '\n';
		}

	}

}