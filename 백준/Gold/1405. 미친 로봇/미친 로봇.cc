#include <iostream>
#include <math.h>
using namespace std;

int N, east, west, south, north;
bool visited[29][29];
double ans = 1.0;

void solve(int cnt, int e, int w, int s, int n){
    if (cnt > N) return;
    if (visited[e - w + 14][s - n + 14]) {
        double tmp = 1.0;
        tmp *= pow(east, e);
        tmp *= pow(west, w);
        tmp *= pow(south, s);
        tmp *= pow(north, n);
        tmp /= pow(100, cnt);
        ans -= tmp;
        return;
    } 
    visited[e - w + 14][s - n + 14] = true;

    solve(cnt + 1, e + 1, w, s, n);
    solve(cnt + 1, e, w + 1, s, n);
    solve(cnt + 1, e, w, s + 1, n);
    solve(cnt + 1, e, w, s, n + 1);

    visited[e - w + 14][s - n + 14] = false;
}

int main(){
    scanf("%d%d%d%d%d", &N, &east, &west, &south, &north);

    solve(0, 0, 0, 0, 0);
    
    printf("%.10lf", ans);


}