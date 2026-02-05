#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int n, k;
	cin >> n >> k;

	vector<int> cards(n);

	for (int i = 0; i < n; i++) cin >> cards[i];

	sort(all(cards));

	set<int> s;

	do { 
		int sum = 0;

		for (int i = 0; i < k; i++) { 
			if (cards[i] < 10) sum *= 10;
			else sum *= 100;

			sum += cards[i];
		}

		s.emplace(sum);
	} while (next_permutation(all(cards)));

	cout << s.size();



}
