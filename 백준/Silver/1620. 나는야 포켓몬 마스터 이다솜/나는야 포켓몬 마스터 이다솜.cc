

#include <iostream>
#include <map>
#include <string>
using namespace std;

map<string, int> dict;
map<int, string> inverseDict;
char pokemon[21];

int main(){
    int N, M;

    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; i++){
        scanf("%s", pokemon);
        dict.insert({pokemon, i});
        inverseDict.insert({i, pokemon});
    }

    for (int i = 0; i < M; i++){
        scanf("%s", pokemon);
        if (pokemon[0] >= '0' && pokemon[0] <= '9'){
            printf("%s\n", inverseDict[stoi(pokemon)].c_str());
        }
        else {
            printf("%d\n", dict[pokemon]);
        }
    }
}