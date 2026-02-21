#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
typedef long long ll;

int main() { 
	fastio;

	int N;
	cin >> N;

	int pineapple = 0, blueberry = 0;

	int prev_t = -1, prev_a = 0, prev_b = 0;

	for (int i = 0; i < N; i++) { 
		int t, a, b;
		cin >> t >> a >> b;

		int point = 100;
		if (a == prev_a && t - prev_t <= 10) point += 50; 

		if (a < 5) pineapple += point;
		else blueberry += point;

		prev_t = t;
		prev_a = a;
		prev_b = b;
	}

	cout << pineapple << ' ' << blueberry;


}
