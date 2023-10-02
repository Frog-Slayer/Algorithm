#include <iostream>
#include <queue>
using namespace std;

int N, M;
int x, y;
int ladder[101];
int minCount[101];

int main(){
	scanf("%d%d", &N, &M);
	for (int i = 0; i < 101; i++) minCount[i] = 2147483600;

	for (int i = 0; i < N + M ; i++){
		scanf("%d%d", &x, &y);
		ladder[x] = y;
	}

	queue<int> q;
	minCount[1] = 0;
	q.push(1);

	while (!q.empty()){
		int front = q.front();
		q.pop();
		if (ladder[front]) {//만약 해당 자리에 뱀이나 사다리가 있으면 그쪽으로 바로 이동
			minCount[ladder[front]] = minCount[front];
			q.push(ladder[front]);
			continue;
		}

		//그렇지 않은 경우
		for (int i = 1; i <= 6; i++){//주사위를 굴려보자
			if (front + i > 100) continue;//만약 주사위를 굴려서 100을 넘어가면 패스
			if (minCount[front] + 1 < minCount[front + i]) {//만약 최단 카운트가 갱신되면
				minCount[front + i] = minCount[front] + 1;
				q.push(front + i);//큐에 넣어줌
			}
		}
	}

	printf("%d", minCount[100]);
}