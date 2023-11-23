#include <iostream>
using namespace std;

int maxSizeOfTree[20];

int countPossibleTree(int idx){
    if (maxSizeOfTree[idx]) return maxSizeOfTree[idx];

    int ret = 0;

    for (int i = 0; i < idx; i++){
        ret += countPossibleTree(i) * countPossibleTree(idx - 1 - i);
    }
    
    return maxSizeOfTree[idx] = ret;
}

void retrieve(int start, int end, int index){
    for (int i = start; i < end; i++){//루트 알파벳이 이거라고 하자
        //루트 알파벳을 기준으로 가능한 경우의 수를 계산
        int left = maxSizeOfTree[i - start];
        int right = maxSizeOfTree[(end - 1) - i];
        int numOfCase = left * right;
        
        //현재 구하려고 하는 index가 경우의 수보다 큰 경우, 지금의 루트 알파벳으로는 불가능. 뺴주고 다음 케이스를 본다
        if (index >= numOfCase) {
            index -= numOfCase;
            continue;
        }
        //그렇지 않은 경우에는 가능
        int leftIndex = index / right;
        int rightIndex = index % right; 
        // printf("leftIndex: %d, rightIndex: %d\n", leftIndex, rightIndex);
        printf("%c", 'a' + i);

        retrieve(start, i, leftIndex);
        retrieve(i + 1, end, rightIndex);
        return;
    }
}

int main(){
    int N, index;
    scanf("%d%d", &N, &index);

    maxSizeOfTree[0] = 1;
    maxSizeOfTree[1] = 1;

    countPossibleTree(N);

    if (index > maxSizeOfTree[N]) {
        printf("-1");
        return 0;
    }

    retrieve(0, N, index - 1);
}