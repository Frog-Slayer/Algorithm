#include <iostream>
#include <set>
#include <string>
using namespace std;

set<string> s;
set<string> ans;
char name[21];

int main(){
    int N, M;
    scanf("%d%d", &N, &M);

    for (int i = 0; i < N; i++){
        scanf("%s", name);
        s.insert(name);
    }

    for (int i = 0; i < M; i++){
        scanf("%s", name);
        if (s.count(name)) ans.insert(name);
    }

    printf("%d\n", ans.size());

    for (string n : ans){
        printf("%s\n", n.c_str());
    }
    
}