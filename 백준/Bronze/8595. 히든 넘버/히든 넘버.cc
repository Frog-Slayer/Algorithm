#include <iostream>
using namespace std;

char buffer[5000001];

int main(){
	int n;
	scanf("%d", &n);
	scanf("%s", buffer);

	int num = 0;
	long long sum = 0;

	for (int i = 0; i < n; i++) {
		if (buffer[i] >= '0' && buffer[i] <= '9') {
			num *= 10;
			num += buffer[i] - '0';
		}
		else {
			sum += num;
			num = 0;
		}
	}
	sum += num;

	printf("%lld", sum);

}