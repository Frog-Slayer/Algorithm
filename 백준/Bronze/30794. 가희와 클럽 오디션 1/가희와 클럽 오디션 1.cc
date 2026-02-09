#include <iostream>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int lv;
	string score;

	cin >> lv >> score;

	map<string, int> m;
	m["miss"] = 0;
	m["bad"] = 200;
	m["cool"] = 400;
	m["great"] = 600;
	m["perfect"] = 1000;

	cout << lv * m[score];
}
