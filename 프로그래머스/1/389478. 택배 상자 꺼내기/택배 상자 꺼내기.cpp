#include <string>
#include <iostream>
#include <vector>

using namespace std;

int solution(int n, int w, int num) {
    int box[100][100] = { 0, };
    
    int row = 0, col = 0;
    pair<int, int> target;
    bool to_right = true;
    
    for (int i = 1; i <= n; i++) { 
        box[row][col] = i;
        if (i == num)  target = {row, col};
        
        if (to_right) { 
            if (col == w - 1) { 
                row++;
                to_right = false;
            }
            else col++;
        }
        else { 
            if (col == 0) { 
                row++;
                to_right = true;
            }
            else col--;
        }
    }
    
    int ans = 0;
    
    for (int i = 0; i <= row; i++) { 
        for (int j = 0; j < w; j++) cout << box[i][j];
        cout << '\n';
    }
    
    
    for (int i = target.first ; i <= row; i++) if (box[i][target.second]) ans++;
    
    return ans;
}