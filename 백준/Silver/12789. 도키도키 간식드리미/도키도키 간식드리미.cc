#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int N;
queue<int> line;
stack<int> side;

int main(){
    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        int x;
        scanf("%d", &x);
        line.push(x);
    }    

    int latest = 0;

    while (true){
        if (!line.empty()) {
            if (line.front() == latest + 1){
                line.pop();
                latest++;
                continue;
            }
        } 
        if (!side.empty()){
            if (side.top() == latest + 1){
                side.pop();
                latest++;
                continue;
            }
        }
        if (!line.empty()){
            int front = line.front();
            line.pop();
            side.push(front);
            continue;
        }
        break;
    }
    if (latest == N) printf("Nice");
    else printf("Sad");
}