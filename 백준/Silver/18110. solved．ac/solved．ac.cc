#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int N;
vector<int> v;

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		int lv;
		scanf("%d", &lv);
		v.push_back(lv);
	}

	sort(v.begin(), v.end());
	int a = round(0.15 * N);

	int sum = 0;
	for (int i = a; i < N - a; i++){
		sum += v[i];
	}

	int avg = round(1.0 * sum / (N - 2 * a));
	
	printf("%d", N ? avg : 0);

}