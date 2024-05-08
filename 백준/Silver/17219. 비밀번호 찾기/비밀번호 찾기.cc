#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int N, M;
char buffer_site[21], buffer_pw[21];
unordered_map<string, string> m;

int main(){
	scanf("%d%d", &N, &M);
	
	for (int i = 0; i < N; i++){
		scanf("%s%s", buffer_site, buffer_pw);
		m.insert({string(buffer_site), string(buffer_pw)});
	}

	for (int i = 0; i < M; i++){
		scanf("%s", buffer_site);
		printf("%s\n", m[string(buffer_site)].c_str());
	}

}