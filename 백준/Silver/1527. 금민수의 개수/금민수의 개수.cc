#include <iostream>
using namespace std;

int main(){
	int A, B, cnt = 0;

	scanf("%d%d", &A, &B);

	for (int i = 2; i < (1<< 10); i++){
		int tmp = i;
		int len = 0;
		while (tmp != 1){
			tmp >>= 1;
			len++;
		}

		int num = 0;		

		for (int j = len - 1; j >= 0; j--){
			num *= 10;
			if ((1 << j) & i) {
				num += 7;
			} 
			else num += 4;
		}

		if (num >= A && num <= B) cnt++;
	}

	printf("%d", cnt);

}