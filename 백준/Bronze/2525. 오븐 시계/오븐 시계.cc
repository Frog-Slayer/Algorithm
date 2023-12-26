#include <iostream>
using namespace std;

int main(){
	int A, B, C;
	scanf("%d%d", &A, &B);

	scanf("%d", &C);

	B += C;
	int t = B / 60;
	B %= 60;

	A += t;

	while (A > 23) A -= 24;

	printf("%d %d", A, B);
}