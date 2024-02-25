#include <iostream>
using namespace std;

int N;

int main(){
    scanf("%d", &N);

    int ans = 4;

    for (int i = 4; i <= N; i++){
        int tmp = i;
        bool isGumminsu = true;
        while (tmp){
            if (tmp % 10 != 4 && tmp % 10 != 7){
                isGumminsu = false;
                break;
            } 
            tmp /= 10;
        }

        if (isGumminsu) ans = i;
    }

    printf("%d", ans);

}