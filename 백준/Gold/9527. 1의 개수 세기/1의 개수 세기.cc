#include <iostream>
using namespace std;

long long A, B;
long long counts[64];//  

long long findOnes(long long num){
	if (num == 1) return 1;
	if (num == 0) return 0;

	//find the biggest 2^n smaller than num
	int leadingOneIndex = 0; 
	long long temp = num;
	while (temp){
		temp /= 2;
		leadingOneIndex++;
	}
	leadingOneIndex--;
	long long ret = findOnes(num - (1LL << leadingOneIndex)) + (num - (1LL << leadingOneIndex)+ 1) + counts[leadingOneIndex - 1];
	return ret;
}

int main(){
	scanf("%lld%lld", &A, &B);
	counts[0] = 1;

	for (int i = 1; i < 55; i++){
		counts[i] = 2 * counts[i - 1] + (1LL << i);
	}	
	
	printf("%lld", findOnes(B) - findOnes(A - 1));
}