#include <stdio.h>
#include <stack>
#include <algorithm>
#define LL long long
using namespace std;

int N;
pair<LL, LL> vertex[100000];
stack<int> stk;


bool compareY(pair<LL, LL> a, pair<LL, LL>b) {
	if (a.second == b.second) return a.first < b.first;
	else return a.second < b.second;
}

long long CCW(pair<LL, LL>a, pair<LL, LL>b, pair<LL, LL>c) {
	return (b.first - a.first)*(c.second - a.second) - (b.second - a.second)*(c.first - a.first);
}

long long calcDist(pair<LL, LL> a){
	return (a.first - vertex[0].first) * (a.first - vertex[0].first) + (a.second - vertex[0].second) * (a.second - vertex[0].second);
}

bool compareA(pair<LL, LL>a, pair<LL, LL>b) {
	long long ccw = CCW(vertex[0], a, b);
	if (ccw) return ccw > 0;
	return calcDist(a) < calcDist(b);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%lld%lld", &vertex[i].first, &vertex[i].second);
	}
	//graham algorithm
	sort(vertex, vertex + N, compareY); //y좌표 순으로 정렬하고
	sort(vertex+1, vertex + N, compareA); //가장 밑에 있는 정점을 기준으로 반시계 방향 정렬
	stk.push(0);
	stk.push(1);
	int next = 2;
	
	while (next < N) {
		while (stk.size() >= 2) {
			int second = stk.top();
			stk.pop();
			int first = stk.top();
			if (CCW(vertex[first], vertex[second], vertex[next]) > 0) {
				stk.push(second);
				break;
			}
		}
		stk.push(next++);
	}

	printf("%ld", stk.size());
}