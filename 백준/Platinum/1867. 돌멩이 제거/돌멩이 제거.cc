#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 501;	
int N, K;
vector<vector<int>> task;
bool visited[MAXN];
int by[MAXN];

bool match(int a){
	if (visited[a]) return false;
	visited[a] = true;
	for (int possibleTask : task[a]){
		if (!by[possibleTask] || match(by[possibleTask])){
			by[possibleTask] = a;
			return true;
		}
	}
	return false;
} 

int main(){
	scanf("%d%d", &N, &K);
	task.resize(N + 1);

	for (int i = 0; i < K; i++){
        int row, col;
		scanf("%d%d", &row, &col);

        task[row].push_back(col);
	}

	int ans = 0;
	for (int i = 1; i <= N; i++){
		for (int j = 0; j <= N; j++) visited[j] = false;
		if (match(i)) ans++;
	}

	printf("%d", ans);
}