#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

const int MAX_BUFFER = 2000;
int C, N, Q;
char buffer[MAX_BUFFER + 1];
set<string> nickname;

class Node{
    public : 
        map<char, Node*> child;
        Node(){}

        void insert(string& word, int idx){
            if (!word[idx]){
                child['*'] = new Node();
                return;
            }
            if (child.count(word[idx])) {
                child[word[idx]]->insert(word, idx + 1);            
            }
            else {
                child[word[idx]] = new Node();
                child[word[idx]]->insert(word, idx + 1);
            }
        }

        bool find(string& word, int idx){
            // printf("%s) %d %c\n", findingNickname? "nick" : "color", idx, word[idx]);

            if (idx == word.length()) return false;
            bool ret = false;

            if (child.count(word[idx])){
                ret |= child[word[idx]]->find(word, idx + 1);
            }

            if (child.count('*')){//끝에 도달?
                ret |= nickname.count(word.substr(idx, word.size()));
            }

            return ret; 
        }
} color;

int main(){
    scanf("%d%d", &C, &N);

    for (int i = 0; i < C; i++){
        scanf("%s", buffer);
        string s = string(buffer);
        color.insert(s, 0);
    }

    for (int i = 0; i < N; i++){
        scanf("%s", buffer);
        nickname.insert(buffer);
    }

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++){
        scanf("%s", buffer);
        string s = string(buffer);

        printf("%s\n", color.find(s, 0) ? "Yes" : "No");
    }

}