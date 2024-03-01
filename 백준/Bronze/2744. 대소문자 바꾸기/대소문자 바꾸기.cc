#include <iostream>
using namespace std;

int main(){
    char word[101] = {0, };
    scanf("%s", word);

    for (int i = 0; word[i]; i++){
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] -= 'a';
            word[i] += 'A';
        }
        else {
            word[i] -= 'A';
            word[i] += 'a';
        }
    }

    printf("%s", word);
}