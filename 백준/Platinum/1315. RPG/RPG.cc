#include <iostream>
#include <stack>
using namespace std;

const int MAXN = 50;

int N;
int STR[MAXN], INT[MAXN], PNT[MAXN];
bool cleared[MAXN];
int maxQuestCount[1001][1001];

int clearQuest(int strength, int intelligence){
    
    if (maxQuestCount[strength][intelligence] != -1) return maxQuestCount[strength][intelligence];

    int ret = 0;
    int point = 0;
    stack<int> stk;

    for (int i = 0; i < N; i++){//깰 수 있는 퀘스트들은 전부 깨고 포인트 싹 모음
        if (strength < STR[i] && intelligence < INT[i]) continue;//현재 스탯으로 깰 수 없는 퀘스트도 제외
        ret++;//현재 스탯으로 깰 수 있는 모든 퀘스트의 수 

        if (cleared[i]) continue;//이미 클리어한 퀘스트는 제외
        //아직 클리어하지 않은 퀘스트인 경우 
        cleared[i] = true;
        stk.push(i);
        point += PNT[i];
    }

    maxQuestCount[strength][intelligence] = ret;

    for (int i = 0; i <= point; i++){
        int st = min(1000, strength + i);
        int in = min(1000, intelligence + (point -i));
        ret = max(ret, clearQuest(st, in));
    }

    while (!stk.empty()) {
        cleared[stk.top()] = false;
        stk.pop();
    }

    return maxQuestCount[strength][intelligence] = ret;
}

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &STR[i], &INT[i], &PNT[i]);
    }

    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 1001; j++) maxQuestCount[i][j] = -1;
    }

    printf("%d", clearQuest(1, 1));
}