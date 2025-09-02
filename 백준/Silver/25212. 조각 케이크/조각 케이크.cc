#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct Frac {
	ll up;
	ll down;

	Frac(ll up, ll down) : up(up), down(down) {}

	Frac operator+(const Frac &o){
		Frac ret(up * o.down + down * o.up, down * o.down);
		return ret.reduce();
	}

	Frac reduce(){ 

		return *this;
	}

	bool operator<=(const Frac &o) {
		return up * o.down <= down * o.up;
	}

	bool operator>=(const Frac &o) {
		return up * o.down >= down * o.up;
	}
};

int main() {
	
	int N, P;
	cin >> N;

	vector<int> c(N);

	for (int i = 0; i < N; i++) cin >> c[i];

	int cnt = 0;

	for (int i = 0; i < (1 << N); i++) {
		Frac f(0, 1);

		for (int j = 0; j < N; j++) { 
			if (i & (1 << j)) { 
				f = f + Frac(1, c[j]);
			}
		}

		if (f >= Frac(99,100) && f <= Frac(101,100)) cnt++;
	}


	cout << cnt;
}

