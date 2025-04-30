#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;
	
	int M;
	cin >> M;

	unordered_map<int, int> m;

	for (int i = 0; i < M; i++) {
		int cmd; 
		cin >> cmd;

		if (cmd == 1) {
			int x, w;
			cin >> x >> w;

			m[w] = x;
		}
		else {
			int w;
			cin >> w;

			cout << m[w] << '\n';
		}
	
	}
	
}
