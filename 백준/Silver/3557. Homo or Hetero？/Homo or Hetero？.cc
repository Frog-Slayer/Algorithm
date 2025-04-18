#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef int RET_TYPE;

#define NEITHER 0
#define HOMO 1
#define HETERO 2
#define BOTH 3

unordered_map<int, int> cnt;
unordered_set<int> homo;
unordered_set<int> occurence;

string get_type(){
	RET_TYPE ret = NEITHER;
	
	if (!homo.empty()) ret |= HOMO;
	if (occurence.size() > 1) ret |= HETERO;

	switch (ret) {
		case NEITHER: return "neither";
		case HOMO: return "homo";
		case HETERO: return "hetero";
	}

	return "both";
}

int main() {
	fastio;

	int N;
	cin >> N;
	cin.ignore();

	for (int i = 0; i < N; i++) {
		string s;
		getline(cin, s);

		int len = s.length();
		int j = 0;

		while (j < len) {
			if (j && s[j - 1] == ' ') break;
			j++;
		}

		int num = stoi(s.substr(j));

		if (s[0] == 'i'){
			cnt[num]++;

			occurence.insert(num);
			if (cnt[num] > 1) homo.insert(num);
		}
		else if (cnt[num]){
			cnt[num]--;
			if (!cnt[num]) occurence.erase(num);
			if (cnt[num] < 2) homo.erase(num);
		}

		cout << get_type() << '\n';
	}
}
