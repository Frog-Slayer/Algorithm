#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() {
	int a, b;

	for (int i = 1; i <= 9; i++) { 
		cout << "? A " << i << '\n';

		int resp;

		cin >> resp;

		if (resp == 1){ 
			a = i;
			break;
		}
	}

	for (int i = 1; i <= 9; i++) { 
		cout << "? B " << i << '\n';

		int resp;

		cin >> resp;

		if (resp == 1){ 
			b = i;
			break;
		}
	}
	cout << "! " << a + b;
}
