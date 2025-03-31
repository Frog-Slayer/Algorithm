#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	bool valid = true;
	string prev;

	vector<vector<bool>> board(6, vector<bool>(6));

	vector<string> v;
	
	for (int i = 0; i < 36; i++) {
		string s;
		cin >> s;
		v.emplace_back(s);
	}

	for (int i = 0; i < 36; i++) {
		string &cur = v[i];
		string &prev = v[(i + 35) % 36];
	
		int x = cur[0] - 'A', y = cur[1] - '0';
		int prevx = prev[0] - 'A', prevy = prev[1] - '0';

		if (board[x][y]) valid = false;
		board[x][y] = true;
		
		if ((abs(x - prevx) == 2  && abs(y - prevy) == 1) || (abs(x - prevx) == 1  && abs(y - prevy) == 2)) continue;
		valid = false;
	}


	cout << (valid ? "Valid" : "Invalid");
}
