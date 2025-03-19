#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;
	
	string a;
	string b;

	while (getline(cin, a), getline(cin, b)) {

		int cnt_a[26] = {0,}, cnt_b[26] = {0,};

		for (char &c : a) cnt_a[c - 'a']++;
		for (char &c : b) cnt_b[c - 'a']++;

		for (int i = 0; i < 26; i++) {
			int cnt = min(cnt_a[i], cnt_b[i]);
			for (int j = 0; j < cnt; j++) cout << (char)(i + 'a');
		}

		cout << '\n';
	}
}
