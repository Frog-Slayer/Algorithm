#include <iostream>
#include <stack>
#include <vector>
#include <string.h>
using namespace std;

char str[1000001], explode[37];
vector<char> ans;
stack<char> stk1, stk2;

int main(){
	scanf("%s", str);
	scanf("%s", explode);

	int len = strlen(str);
	int expLen = strlen(explode);

	int idx = 0;

	for (int i = 0; i < len; i++){
		stk1.push(str[i]);
		if (stk1.top() == explode[expLen - 1]){
			for (int j = expLen-1; !stk1.empty() && j >= 0; j--){
				if (stk1.top() == explode[j]) {
					stk2.push(stk1.top());
					stk1.pop();
				}
				else break;
			}
			if (stk2.size() == expLen) {
				while (!stk2.empty()) stk2.pop();
			}
			else {
				while (!stk2.empty()) {
					stk1.push(stk2.top());
					stk2.pop();
				}
			}
		}			
	}	

	if (stk1.empty()){
		printf("FRULA");
	}
	else {
		while (!stk1.empty()) {
			ans.push_back(stk1.top());
			stk1.pop();
		}
		for (int i = ans.size() - 1; i >= 0; i--) printf("%c", ans[i]);
	}
}