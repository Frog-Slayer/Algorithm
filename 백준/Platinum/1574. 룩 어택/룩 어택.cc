#include <iostream>
#include <vector>
using namespace std;

const int MAXRC = 300;
int R, C, N;
int invAdj[MAXRC + 1][MAXRC + 1];
vector<vector<int>> task;
int by[MAXRC * 2 + 1];
bool visited[MAXRC * 2 + 1];

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
    scanf("%d%d%d", &R, &C, &N);
    task.resize(R + C + 1);

    for (int i = 0; i < N; i++){
        int row, col;
        scanf("%d%d", &row, &col);
        invAdj[row][col] = true;
    }

    for (int i = 1; i <= R; i++){
        for (int j = 1; j <= C; j++){
            if (invAdj[i][j]) continue;
            task[i].push_back(j + R);
        }
    }

    int ans = 0;

    for (int i = 1; i <= R + C; i++){
        for (int j = 1; j <= R + C; j++) visited[j] = false;
        if (match(i)) ans++; 
    }
    
    printf("%d", ans);

}