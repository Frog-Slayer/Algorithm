#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() { 
	fastio;

	int A, B, C, D;
	cin >> A >> B >> C >> D;

	int P, M, N;
	cin >> P >> M >> N;

	vector<bool> dog1(1000), dog2(1000);

	int dog1_attack = A, dog1_rest = B, dog2_attack = C, dog2_rest = D;

	for (int i = 0; i < 1000; i++) { 
		if (dog1_attack) dog1[i] = true, dog1_attack--;
		else if (dog1_rest) { 
			dog1_rest--;
			if (!dog1_rest) dog1_attack = A, dog1_rest = B;
		}

		if (dog2_attack) dog2[i] = true, dog2_attack--;
		else if (dog2_rest) { 
			dog2_rest--;
			if (!dog2_rest) dog2_attack = C, dog2_rest = D;
		}
	}

    P--;
	M--;
	N--;
    
	cout << dog1[P] + dog2[P] << '\n';
	cout << dog1[M] + dog2[M] << '\n';
	cout << dog1[N] + dog2[N] << '\n';
}
