#include <iostream>
#include <deque>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()


int main() { 
	fastio;

	int N;
	cin >> N;

	deque<char> deq;
	deque<int> order;

	for (int i = 0; i < N; i++) { 
		int a;
		char c;

		cin >> a;

		if (a == 1) { 
			cin >> c;
			deq.emplace_back(c);
		}
		else if (a == 2) { 
			cin >> c;
			deq.emplace_front(c); 
		}
		else  { 
			if (deq.empty()) continue; 
			if (order.empty()) continue;

			int prev = order.back();
			order.pop_back();

			if (prev == 1) deq.pop_back();
			else deq.pop_front();
		}

		if (a < 3) order.emplace_back(a);
	}

	if (deq.empty()) cout << 0;
	else for (char c : deq) cout << c;

}
