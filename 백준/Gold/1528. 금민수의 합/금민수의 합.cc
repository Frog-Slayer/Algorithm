#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;
int N;

int dist[MAXN], prevNum[MAXN];
vector<int> v, ans;
queue<int> q;

int main(){
    scanf("%d", &N);

    for (int i = 2; i < (1 << 7); i++){
        int gum = 0;
        int tmp = i;
        int len = 0;

        while (tmp != 1){
            len++;
            tmp >>= 1;
        }

        for (int j = len - 1; j >= 0; j--){
            gum *= 10;
            if ((1 << j) & i) gum += 7;
            else gum += 4;
        }

        if (gum <= N) {
            q.push(gum);
            v.push_back(gum);
            dist[gum] = 1;
        }
    }

    while (!q.empty()){
        int p = q.front();
        q.pop();

        if (p == N) break;

        for (int i = 0; i < v.size(); i++){
            int next = p + v[i];
            if (next > N) break;
            if (dist[next] && dist[next] <= dist[p] + 1) continue;
            dist[next] = dist[p] + 1;
            prevNum[next] = p;
            q.push(next);
        }
    }

    if (!dist[N]) printf("-1");
    else {
        int idx = N;
        while (idx){
            ans.push_back(idx - prevNum[idx]);
            idx = prevNum[idx];
        }
        sort(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
    }
}