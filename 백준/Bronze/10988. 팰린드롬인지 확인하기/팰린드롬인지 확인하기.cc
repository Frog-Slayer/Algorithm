#include <iostream>
#include <string.h>
using namespace std;

int main(){
    char s[101];
    scanf("%s", s);
    int len = strlen(s);

    int palindrome = 1;
    for (int i = 0; i < len; i++){
        char start = s[i], end = s[len - 1 - i];
        if (start != end) palindrome = 0;
    }

    printf("%d", palindrome);

}