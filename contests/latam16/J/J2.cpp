#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef long long int ll;
int n;

int main () {
	scanf("%d", &n);
	double p0 = 0, p1 = 1. / (n);
	int p = -1; double mn = 1./0.;
	for(int i = 1; i < n; i++) {
		p0 = (1. - p0) / (n);
		p1 = (1. - p1) / (n);
		printf("[%2d] %.10f %.10f\n", i+1, p0, p1);
		if(p0 < mn) mn = p0, p = i;
	}
	printf(">>[%d] %.20f\n", p+1, mn);
}
