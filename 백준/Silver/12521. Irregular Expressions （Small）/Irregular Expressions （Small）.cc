#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int count_vowels(string s) { 
	int cnt = 0;

	for (char &c : s) { 
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') cnt++;
	}

	return cnt;
}

bool check(string s) { 
	int length = s.size();

	for (int i = 1; i < length; i++) { 
		string front = s.substr(0, i);

		if (count_vowels(front) < 2) continue;

		string end = s.substr(length - i, i);

		if (count_vowels(end) < 2 || front != end) continue;

		int mid_len = length - 2 * i;

		if (mid_len < 1) continue;
		if (!count_vowels(s.substr(i, mid_len))) continue;

		return true;
	}

	return false;
}

bool contains_spell(string s) { 
	int len = s.size();

	for (int i = 0; i < len; i++) { 
		for (int j = 1; i + j <= len; j++) { 
			if (check(s.substr(i, j))) return true;
		}
	}

	return false;
}

int main () { 
	fastio;

	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) { 
		string spell;
		cin >> spell;

		bool is_spell = contains_spell(spell);

		cout << "Case #" << i << ": " << (is_spell ? "Spell!\n" : "Nothing.\n");
	}

}
