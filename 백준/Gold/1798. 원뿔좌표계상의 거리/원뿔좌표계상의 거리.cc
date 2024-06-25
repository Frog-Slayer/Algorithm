#include <stdio.h>
#include <math.h>
#include <tuple>
#define _USE_MATH_DEFINES
using namespace std;

typedef tuple<double, double, double> tddd;

double to_radius(double angle){
	return angle / 180 * M_PI;
}

int main() {

	double R, H, d1, a1, d2, a2;
	while (scanf("%lf%lf%lf%lf%lf%lf", &R, &H, &d1, &a1, &d2, &a2) != EOF){
		double angle = min(abs(a1 - a2), 360 - abs(a1- a2)) * R / sqrt(R * R + H * H);
		angle = to_radius(angle);
		double ans = sqrt(d1 * d1 + d2 * d2 - 2 * d1 * d2 * cos(angle));
		printf("%.2lf\n", ans);
	}
}