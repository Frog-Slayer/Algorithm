#include <iostream>
using namespace std;

char init[51];
char S[51];
int loops, from, to;
long long len[31];
int initLen, dollarCnt, nonDollarCnt;

char findChar(int n, int idx){//S가 $...$...$ 꼴이라 할 때, S_n = [S_{n-1}]...[S_{n-1}]...[S_{n-1}]
    long long tmp = 0;

    if (n == 1){
        for (int i = 0; i < dollarCnt + nonDollarCnt; i++){
            if (S[i] == '$'){
                for (int j = 0; j < initLen; j++){
                    if (tmp == idx) return init[j];
                    tmp++; 
                }
            }
            else {
                if (tmp == idx) return S[i];
                tmp++;
            }
        }
    }
    else {
        for (int i = 0; i < dollarCnt + nonDollarCnt; i++){
            if (S[i] == '$'){
                if (tmp <= idx && idx < tmp + len[n - 1]) return findChar(n - 1, idx - tmp);
                tmp += len[n-1];
            }
            else {
                if (tmp == idx) return S[i];
                tmp++;
            } 
        }
    }

    return '-';
} 

int main(){
    scanf("%s", init);
    for (int i = 0; init[i]; i++) initLen++;

    scanf("%s", S);

    for (int i = 0; S[i]; i++) {
        if (S[i] == '$') dollarCnt++;
        else nonDollarCnt++;
    }

    scanf("%d", &loops);
    scanf("%d%d", &from, &to);

    if (dollarCnt == 1) {
        long long total = 0;
        bool dollarEnc = false;
        long long front = 0, back = 0;

        for (int i = 0; S[i]; i++){
            if (S[i] == '$') dollarEnc = true; 
            else if (dollarEnc) back++;
            else front++;
        }

        total = (loops * front) + (loops * back) + initLen;

        //$ 앞에 있는 걸 n회 반복 - init - 뒤 loops회 반복
        //total보다 큰 자리는 모두 '-'로 출력
        for (long long i = from - 1; i < to; i++){
            if (i < front * loops){
                printf("%c", S[i % front]);
            }
            else if (i < front * loops + initLen){
                long long j = i - front * loops;
                printf("%c", init[j]);
            }
            else if (i < total) {
                long long j = i - (front * loops + initLen);
                printf("%c", S[front + 1 + (j % back)]);
            }
            else printf("-");
        }
    }
    else {
        len[1] = dollarCnt * (initLen) + nonDollarCnt; 

        for (int i = 2; i <= loops; i++){
            len[i] = dollarCnt * (len[i - 1]) + nonDollarCnt;
            if (len[i] > to) {
                loops = i;
                break;
            }
        }

        for (long long i = from - 1; i < to; i++){
            printf("%c", findChar(loops, i));
        }
    }
}