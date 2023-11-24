#include <iostream>
using namespace std;

const int MAXN = 100000;
int N, num, ans;

class Node {
public : 
    Node *left = NULL;//1
    Node *right = NULL;//0

    void addTree(int val, int pos){
        if (pos < 0) return;
        int bit = val & (1 << pos);

        if (bit){
            if (left != NULL){
                left->addTree(val, pos - 1);
            }
            else {
                left = new Node();
                left->addTree(val, pos - 1);
            }
        }
        else {
            if (right!= NULL){
                right->addTree(val, pos - 1);
            }
            else {
                right = new Node();
                right ->addTree(val, pos - 1);
            }
        }
    }
};

Node *root = new Node();

int compare(int ret, int level, Node *node1, Node *node2){
    if (node1 == NULL || node2 == NULL) return 0;
    if (level < 0) return ret;
    int result = 0; 
    //note : left에 1, right에 0
    Node* left1 = node1->left;
    Node* right1 = node1->right;
    Node* left2 = node2->left;
    Node* right2 = node2->right;
    
    int tmp = ret + (1 << level);
    if ((left1 != NULL && right2 != NULL) || (right1 != NULL && left2 != NULL)) {
        result = max(result, compare(tmp, level - 1, left1, right2));
        result = max(result, compare(tmp, level - 1, right1, left2));
    }
    else {
        result = max(result, compare(ret, level - 1, left1, left2));
        result = max(result, compare(ret, level - 1, right1, right2));
    }
    return result;
}


int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        scanf("%d", &num); 
        root->addTree(num, 30);
    }

    int ret = compare(0, 30, root, root);

    printf("%d", ret);
}