#include <stdio.h>
#include <set>
using namespace std;

int T, k, n;
char cmd; 
set<pair<int, int>> Q;

int main(){
	scanf("%d", &T);
	while (T--){
		scanf("%d", &k);
		Q.clear();
		for (int i = 0; i < k; i++){
			scanf(" %c %d", &cmd, &n);

			if (cmd == 'I'){
				Q.insert({n,  i});	
			}
			else {
				if (Q.empty()) continue;
				if (n == 1){//pop max
					Q.erase(--Q.end());
				}
				else {//pop min
					Q.erase(Q.begin());
				}
			}
		}
		if (Q.empty()) printf("EMPTY\n");
		else printf("%d %d\n", (*--Q.end()).first, (*Q.begin()).first);
	}




}