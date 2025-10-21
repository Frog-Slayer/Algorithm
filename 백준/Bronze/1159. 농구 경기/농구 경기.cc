#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;

	int N;
	cin >> N;

	vector<int> cnt(26);
	for (int i = 0; i < N; i++) { 
		string s;
		cin >> s;

		cnt[s[0] - 'a']++;
	}

	bool predaja = true;

	for (int i = 0; i < 26; i++) { 
		if (cnt[i] >= 5) {  
			predaja = false;
			cout << (char)(i + 'a');
		}
	}

	if (predaja) cout << "PREDAJA";
}
