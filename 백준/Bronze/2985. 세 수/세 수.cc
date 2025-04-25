#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()
int a, b, c;

void print1(char op) {
	printf("%d%c%d=%d", a, op, b, c);
}

void print2(char op) {
	printf("%d=%d%c%d", a, b, op, c);
}

int main() {
	scanf("%d%d%d", &a, &b, &c);

	if (a + b == c) print1('+');
	else if (a - b == c) print1('-');
	else if (a * b == c) print1('*');
	else if (a == b * c) print1('/');
	else if (a == b + c) print2('+'); 
	else if (a == b - c) print2('-'); 
	else if (a == b * c) print2('*'); 
	else print2('/');
}

	


