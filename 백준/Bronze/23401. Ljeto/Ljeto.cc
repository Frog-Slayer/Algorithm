#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
typedef long long ll;

int main() { 
	fastio;

	int N;
	cin >> N;
	
	vector<int> last(9, -1);

	int pineapple = 0, blueberry = 0;

	for (int i = 0; i < N; i++) { 
		int t, a, b;
		cin >> t >> a >> b;

		int point = 100;
		if (last[a] != -1 && t - last[a] <= 10) point += 50; 

		if (a < 5) pineapple += point;
		else blueberry += point;

		last[a] = t;
	}

	cout << pineapple << ' ' << blueberry;


}