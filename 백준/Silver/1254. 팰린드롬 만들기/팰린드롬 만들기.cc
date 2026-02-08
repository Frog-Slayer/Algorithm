#include <iostream>
#include <deque>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

bool is_palindrome(deque<char> &deq) { 
	int len = deq.size();

	for (int i = 0; i < len / 2; i++) { 
		if (deq[i] == deq[len - 1 - i]) continue;
		return false;
	}

	return true;
}

int main() { 
	fastio;

	string S;
	cin >> S;

	int len = S.size();

	deque<char> deq;
	for (int i = 0; i < len; i++) deq.emplace_back(S[i]);

	if (is_palindrome(deq)) { 
		cout << len;
		return 0;
	}

	auto it = deq.end();

	for (int i = 0; i < len; i++) { 
		deq.insert(it, S[i]);

		if (is_palindrome(deq)) { 
			cout << (i + 1 + len);
			return 0;
		}
	}
}
