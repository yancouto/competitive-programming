#include <bits/stdc++.h>
using namespace std;

int dv[200000];
int ps[15009], pn;
void pre() {
	int i;
	for(i = 2; pn < 15005; i++) {
		if(dv[i]) continue;
		ps[pn++] = i;
		for(int j = 2 * i; j < 200000; j += i)
			dv[j] = 1;
	}
}


int main() {
	pre();
	int i, n, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &k);
		printf("%d\n", ps[k-1]);
	}
	return 0;
}
