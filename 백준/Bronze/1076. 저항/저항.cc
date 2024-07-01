#include <iostream>
#include <string.h>
using namespace std;

int comp(char* str, bool b){
	int ret = 0;
	if (!strcmp(str, "black")) ret = 0;
	if (!strcmp(str, "brown")) ret = 1;
	if (!strcmp(str, "red")) ret = 2;
	if (!strcmp(str, "orange")) ret = 3;
	if (!strcmp(str, "yellow")) ret = 4;
	if (!strcmp(str, "green")) ret = 5;
	if (!strcmp(str, "blue")) ret = 6;
	if (!strcmp(str, "violet")) ret = 7;
	if (!strcmp(str, "grey")) ret = 8;
	if (!strcmp(str, "white")) ret = 9;

	if (b) return ret;
	int prod = 1;
	while (ret--) prod *= 10;
	return prod;
}

int main(){
	char buffer[7];
	long long ans = 0;

	scanf("%s", buffer);
	ans += comp(buffer, true);

	scanf("%s", buffer);
	ans *= 10;
	ans += comp(buffer, true);

	scanf("%s", buffer);
	ans *= comp(buffer, false);

	printf("%lld", ans);
}