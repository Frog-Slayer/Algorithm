#include <iostream>
#include <queue>
using namespace std;

pair<int, int> triangle[3];
priority_queue<int> pq;

long long pow(long long n){
	return n * n;
}

long long get_dist(pair<int, int> p1, pair<int, int> p2){
	int x_diff = p1.first - p2.first;
	int y_diff = p1.second - p2.second;

	return pow(x_diff) + pow(y_diff);
}

int main(){
	for (int i = 0; i < 3; i++){
		scanf("%d%d", &triangle[i].first, &triangle[i].second);
	}

	for (int i = 0; i < 3; i++) {
		int len = get_dist(triangle[i], triangle[(i + 1) % 3]);
		pq.push(len);
	}

	long long max_sq = pq.top();
	pq.pop();
	long long mid_sq = pq.top();
	pq.pop();
	long long min_sq= pq.top();
	pq.pop();

	if (pow(max_sq - mid_sq - min_sq) == 4 * mid_sq * min_sq) printf("X");
	else if (max_sq == min_sq) printf("JungTriangle");
	else if (max_sq == mid_sq || mid_sq == min_sq) {
		if (max_sq > mid_sq + min_sq) printf("Dunkak2Triangle");
		else if (max_sq == mid_sq + min_sq) printf("Jikkak2Triangle");
		else if (max_sq < mid_sq + min_sq) printf("Yeahkak2Triangle");
	}
	else {
		if (max_sq > mid_sq + min_sq) printf("DunkakTriangle");
		else if (max_sq == mid_sq + min_sq) printf("JikkakTriangle");
		else if (max_sq < mid_sq + min_sq) printf("YeahkakTriangle");
	}
}