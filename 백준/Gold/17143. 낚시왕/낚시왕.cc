#include <iostream>
#include <vector>
using namespace std;

const int MAXRC = 100;
const int UP = 1;
const int DOWN = 2;
const int RIGHT = 3;
const int LEFT = 4;

int R, C, M;
int r, c, s, d, z;
int pool[MAXRC][MAXRC];

class Shark{
	public: 
		int idx;
		int row;
		int col;
		int spd;
		int dir;
		int sz;

		Shark(int idx, int row, int col, int spd, int dir, int sz){
			this->idx = idx;
			this->row = row;
			this->col = col;
			this->spd = spd;
			this->dir = dir;
			this->sz= sz;
		}

		void move(){
			int r = row;
			int c = col;

			if (dir == UP || dir == DOWN) {
				int nextRow = spd;
				int cycle = 2 * (R - 1);
				if (dir == UP) nextRow += 2 * (R - 1) - row;
				else nextRow += row;

				nextRow %= cycle;
				if (nextRow >= R) {
					row = cycle - nextRow;
					dir = UP;
				}
				else {
					row = nextRow;
					dir = DOWN;
				}
			}
			else {
				int nextCol = spd;
				int cycle = 2 * (C - 1);

				if (dir == LEFT) nextCol += 2 * (C - 1) - col;
				else nextCol += col;

				nextCol %= cycle;
				if (nextCol >= C) {
					col = cycle - nextCol;
					dir = LEFT;
				}
				else {
					col = nextCol;
					dir = RIGHT;
				}
			}
		}
};

vector<Shark*> sharks;

int main(){
	scanf("%d%d%d", &R, &C, &M);

	for (int i = 1; i <= M; i++){
		scanf("%d%d%d%d%d", &r, &c, &s, &d, &z);
		sharks.push_back(new Shark(i, r - 1, c - 1, s, d, z));
		pool[r-1][c-1] = i;
	}

	int ans = 0;

	for (int i = 0; i < C; i++){
		for (int j = 0; j < R; j++){
			if (pool[j][i]) {
				Shark* sh = sharks[pool[j][i] - 1];
				if (!sh->sz) continue;
				ans += sh->sz;	
				sh->sz = 0;
				break;
			}
		}

		for (int i = 0; i < M; i++) sharks[i]->move();

		for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) pool[i][j] = 0;

		for (int i = 0; i < M; i++) {
			Shark *sh = sharks[i];
			if (pool[sh->row][sh->col]) {
				Shark *other = sharks[pool[sh->row][sh->col] - 1];
				if (sh->sz < other->sz) sh->sz = 0;
				else {
					other->sz = 0;
					pool[sh->row][sh->col] = sh->idx; 
				}
			}
			else pool[sh->row][sh->col] = sh->idx;
		}
	}
	printf("%d", ans);
}