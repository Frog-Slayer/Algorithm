#include <iostream>
using namespace std;

int N;
char isFriend[50][51];
int friendCount[50];

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        scanf("%s", isFriend[i]);
    }

    int ans = 0;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (i == j) continue;
            if (isFriend[i][j] == 'Y') friendCount[i]++;
            else {
                bool hasFriendInCommon = false;
                for (int k = 0; k < N; k++){
                    if (k == i || k == j) continue;
                    if (isFriend[i][k] == 'Y' && isFriend[j][k] == 'Y'){
                        hasFriendInCommon = true;
                        break;
                    }
                }
                if (hasFriendInCommon) friendCount[i]++;
            }
            ans = max(ans, friendCount[i]);
        }
    } 

    printf("%d", ans);


}