#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

const int INF = 100;

int main() {
	fastio;

	int N;
	cin >> N;
	int total = N * (N - 1) / 2;

	map<string, int> m;

	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		
		m[s] = i;
	}

	vector<string> hyunoo(N);

	int score = 0;

	for (int i = 0; i < N; i++){
		cin >> hyunoo[i];

		for (int j = 0; j < i; j++) {
			if (m[hyunoo[j]] < m[hyunoo[i]]) score++;
		}
	}


	cout << score << '/' << total;
    
}
