#include <bits/stdc++.h>
using namespace std;

int dv[10009];
void pre() {
	int i, j;
	for(i = 2; i < 10009; i++) {
		if(dv[i]) continue;
		for(j = i; j < 10009; j += i)
			dv[j] = i;
	}
}
int all[10009];

int main() {
	int i, x;
	pre();
	for(i = 0; i < 10; i++) {
		scanf("%d", &x);
		while(x != 1) {
			all[dv[x]]++;
			x /= dv[x];
		}
	}
	int tot = 1;
	for(i = 2; i < 10009; i++)
		tot = (tot * (all[i] + 1)) % 10;
	printf("%d\n", tot);
	return 0;
}
