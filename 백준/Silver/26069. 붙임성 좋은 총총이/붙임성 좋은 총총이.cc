#include <iostream>
#include <unordered_set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int N;
	cin >> N;

	unordered_set<string> s;
	s.emplace("ChongChong");

	for (int i = 0; i < N; i++) {
		string A, B;
		cin >> A >> B;

		if (s.count(A)) s.emplace(B);
		else if (s.count(B)) s.emplace(A);
	}

	cout << s.size();

}
