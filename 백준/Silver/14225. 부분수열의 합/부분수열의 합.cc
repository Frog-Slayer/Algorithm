#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int N;
	cin >> N;

	vector<int> S(N);

	for (int i = 0; i < N; i++) cin >> S[i];

	unordered_set<int> us;

	for (int i = 0; i < (1 << N); i++) { 
		int sum = 0;

		for (int j = 0; j < N; j++) { 
			if ((i & (1 << j)) == 0) continue;
			sum += S[j];
		}

		us.emplace(sum);

	}
	
	int i = 1;

	while (true) { 
		if (us.find(i) == us.end()){ 
			cout << i;
			break;
		}

		i++;
	}
}
