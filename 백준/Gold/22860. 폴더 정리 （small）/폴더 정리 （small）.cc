#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int N, M, C, Q;
char P[11], F[11];
char path[15000];
unordered_map<string, int> directoryMap, fileMap;
int dirIdx = 0, fileIdx = 0;

vector<vector<int>> dirAdj, fileAdj;
bool visited[1001];

pair<int, int> query(int path){
    int kindCount = 0, totalCount = 0; 
    for (auto f: fileAdj[path]){
        totalCount++;
        if (visited[f]) continue;
        visited[f] = true;
        kindCount++;
    }

    for (auto dir : dirAdj[path]){
        pair<int, int> res = query(dir);
        kindCount += res.first;
        totalCount += res.second; 
    }

    return { kindCount, totalCount};
}

int main(){
    scanf("%d%d", &N, &M);
    dirAdj.resize(1010);
    fileAdj.resize(1010);

    directoryMap.insert({"main", ++dirIdx});

    for (int i = 0; i < N + M; i++){
        scanf("%s %s %d", P, F, &C);
        string pString = string(P); 
        if (!directoryMap[pString]) directoryMap[pString] = ++dirIdx;

        if (C){//폴더
            string fString = string(F);
            if (!directoryMap[fString]) directoryMap[fString] = ++dirIdx;
            dirAdj[directoryMap[pString]].push_back(directoryMap[fString]);
        }
        else {
            string fString = string(F);
            if (!fileMap[fString]) fileMap[fString] = ++fileIdx; 
            fileAdj[directoryMap[pString]].push_back(fileMap[fString]);
        }
    }

    scanf("%d", &Q);

    for (int i = 0; i < Q; i++){
        scanf("%s", path);
        int len = strlen(path);
        string rev = "";
        for (int i = len-1; i >= 0; i--){
            if (path[i] == '/') break;
            rev += path[i];
        }

        reverse(rev.begin(), rev.end());

        
        for (int j = 0; j <= M; j++) visited[j] = false;
        pair<int, int> res = query(directoryMap[rev]);
        printf("%d %d\n", res.first, res.second);
    }
}