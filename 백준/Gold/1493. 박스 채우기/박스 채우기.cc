#include <iostream>
using namespace std;

int cube[20];
int ans;

bool solve(int l, int w, int h){
	if (!l || !w || !h) return true;
	int s = 0;

	for (int i = 19; i >= 0; i--){
		if (!cube[i]) continue;
		s = (1 << i);

		if (s > l || s > w || s > h) continue;
		cube[i]--;
		ans++;
		bool a = solve(l - s, s ,s);
		bool b = solve(l, w - s, s);
		bool c = solve(l, w, h - s);
		return a && b && c;		
	}
	//넣을 수 있는 게 없음
	return false;
}


int main(){

	int l, w, h;
	scanf("%d%d%d", &l, &w, &h);
	
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		int j;
		scanf("%d", &j);
		scanf("%d", &cube[j]);
	}

	if (solve(l, w, h)) printf("%d", ans);
	else printf("-1");
}