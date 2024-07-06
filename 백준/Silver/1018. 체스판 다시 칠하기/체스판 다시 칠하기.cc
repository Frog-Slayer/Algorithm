#include <iostream>
using namespace std;

int main()
{
	char Bchess[8][8], Wchess[8][8];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0) { Bchess[i][j] = 'B'; Wchess[i][j] = 'W'; }
			else { Bchess[i][j] = 'W'; Wchess[i][j] = 'B'; }
		}
	}
	
	int N, M, Wcount = 0, Bcount = 0, h = 0, min = 2500;
	char board[50][50];
	int count[1850];

	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %c", &board[i][j]);
		}
	}
	
	while (h < (N - 7)*(M - 7)) {
		for (int i = 0; i < N - 7; i++) {
			for (int j = 0; j < M - 7; j++) {

				for (int k = 0; k < 8; k++) {
					for (int l = 0; l < 8; l++) {
						if (board[i + k][j + l] != Wchess[k][l]) Wcount = Wcount + 1;
						if (board[i + k][j + l] != Bchess[k][l]) Bcount = Bcount + 1;
					}
				}

				count[h] = (Wcount < Bcount ? Wcount : Bcount);
				Wcount = 0; Bcount = 0;
				h = h + 1;
			}
		}
	}

	for (int i = 0; i < (N - 7)*(M - 7); i++) {
		if (count[i] <= min) min = count[i];
	}

	printf("%d", min);

}