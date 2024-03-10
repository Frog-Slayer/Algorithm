#include <iostream>
using namespace std;

int main(){
    char s[101];
    int cnt[26] = {0, };
    scanf("%s", s);
    
    for (int i = 0; s[i]; i++){
        cnt[s[i] - 'a']++;
    }
    
    for (int i = 0; i < 26; i++){
        printf("%d ", cnt[i]);
    }
}