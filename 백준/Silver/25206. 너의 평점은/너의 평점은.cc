#include <iostream>
using namespace std;

char sbj[51];
double credit;
char grade[3];

int main() {
	int cnt = 0;
	double ans = 0;

	for (int i = 0; i < 20; i++) {
		scanf("%s %lf %s", sbj, &credit, grade); 
		if (grade[0] == 'P') continue;;
		cnt += credit;
		double s = 0;

		if (grade[0] == 'A') s += 4;
		else if (grade[0] == 'B') s += 3;
		else if (grade[0] == 'C') s += 2;
		else if (grade[0] == 'D') s += 1;

		if (grade[1] == '+') s += 0.5;
	
		ans += s * credit;
	}

	printf("%.6f", ans / cnt);
}