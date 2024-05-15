#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int M, l, r;
vector<pair<int, int>> v;

int main(){
    scanf("%d", &M);

    while (true){
        scanf("%d%d", &l, &r);
        if (!l && !r) break;

        if (l > r) swap(l, r);
        if (r <= 0) continue;
        if (l < 0) l = 0;

        v.emplace_back(l ,r);
    }

    sort(v.begin(), v.end());

    int i = 0, ans = 0, end = 0;
    while (true){
        int max_next_end = -1;
        int max_next_end_idx = -1;
        for (; i < v.size(); i++){
            int s = v[i].first, e = v[i].second;
            if (s <= end && e > end) {
                if (max_next_end < e){
                    max_next_end = e;
                    max_next_end_idx = i;
                }
            }
            else if (s > end) break;
        }

        if (max_next_end_idx != -1) {
            end = max_next_end;
            ans++;
        }
        else break;

        if (end >= M || i > v.size()) break;
    }


    if (end >= M) printf("%d", ans);
    else printf("0");
    
}