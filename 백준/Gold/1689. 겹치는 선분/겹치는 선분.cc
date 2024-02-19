#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, s, e;
vector<pair<int, int>> v;

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        scanf("%d%d", &s, &e);
        v.emplace_back(s, 1);
        v.emplace_back(e, -1);
    }

    sort(v.begin(), v.end());

    int ans = 0, cur = 0;
    for (int i = 0; i < 2 * N; i++){
        ans = max(ans, cur);
        cur += v[i].second;
    }

    printf("%d", ans);
}