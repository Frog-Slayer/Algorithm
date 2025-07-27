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

	int sum = 0, count = 0;

	for (int i = 0, j = 0; i < N; i++) { 
		while (sum < N && j < N) { 
			sum += j + 1;
			j++;
		}

		if (sum == N) count++;
		
		sum -= i + 1;
	}

	cout << count;
}
