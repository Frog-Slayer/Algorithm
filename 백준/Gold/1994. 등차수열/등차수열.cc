#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> v;
bool isChecked[2000][2000];

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        int n;
        scanf("%d", &n);
        v.push_back(n);
    }


    sort(v.begin(), v.end());

    int ans = 1;
    int tmp = 1;

    for (int i = 1; i < N; i++){
        if (v[i] == v[i - 1]) {
            tmp++;
            ans = max(ans, tmp);
        }
        else tmp = 1;
    }

    for (int i = 0; i < N; i++){
        for (int j = i + 1; j < N; j++){
            if (isChecked[i][j]) continue;
            int len = 2;
            int d = v[j]- v[i];
            int cur = v[j];
            
            isChecked[i][j] = true;

            if (d == 0) continue;

            int nextIdx = j;
            while (true) {
                nextIdx = lower_bound(v.begin() + nextIdx, v.end(), cur += d) - v.begin();
                if (nextIdx == N || v[nextIdx] != cur) break;
                // printf("%d ", v[nextIdx]);
                len++;
                isChecked[i][nextIdx] = true;
            }
            // printf("\n");
            ans = max(ans, len);
        }
    }
    printf("%d", ans);
}