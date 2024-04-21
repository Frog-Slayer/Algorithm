#include <iostream>
#include <set>
using namespace std;

set<int> s;

int main(){
    int a, b;
    scanf("%d%d", &a, &b);

    int ans = 0;
    for (int i = 0; i < a; i++){
        int n;
        scanf("%d", &n);
        s.insert(n);
        ans++;
    }

    for (int i = 0; i < b; i++){
        int n;
        scanf("%d", &n);
        if (s.count(n)) ans--;
        else ans++;
    }

    printf("%d", ans);
}