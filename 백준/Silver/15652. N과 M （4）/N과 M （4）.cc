#include <iostream>
using namespace std;

int N, M, pass = 0;
int arr[9];
bool visited[9];

void func(int cnt)
{
 	if (cnt == M)
	{
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < i; j++) if (arr[i] < arr[j]) ++pass;
		}

		if (pass == 0) {
			for (int i = 0; i < M; i++) printf("%d ", arr[i]);
			printf("\n");

		}

		pass = 0;

		return;
	}

	for (int i = 1; i <= N; i++) 
			{
				arr[cnt] = i;
				func(cnt + 1);
			}
}


int main()
{
	scanf("%d %d", &N, &M);
	func(0);
}