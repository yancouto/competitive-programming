#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 3200000;
int dv[MAX];
int ps[284000], dn;
ll pot[14];
void pre() {
	int i;
	for(i = 2; i < MAX; i++) {
		if(dv[i]) continue;
		for(int j = 2*i; j < MAX; j += i)
			dv[j] = 1;
	}
	for(i = 2; i < MAX; i++)
		if(!dv[i])
			ps[dn++] = i;
	pot[0] = 1ll;
	for(i = 1; i < 14; i++)
		pot[i] = pot[i-1] * 10ll;
}

int r[4] = {1, 3, 7, 9};
ll gen(int n, ll x) {
	ll z = r[rand() % 4];
	for(int i = 1; i < n; i++)
		z = z + pot[i] * (rand() % 10);
	return x * pot[n] + z;
}

int main() {
	srand(time(NULL)); rand(); rand();
	int n, i; ll x = 0, z;
	pre();
	scanf("%d", &n);
	if(n) scanf("%lld", &x);
	if(n == 12) { printf("%012lld\n", x); return 0; }
	while(true) {
		z = gen(12 - n, x);
		for(i = 0; i < dn; i++)
			if(!(z % ps[i]))
				break;
		if(i == dn) break;
	}
	if(z == 1) z = 3;
	printf("%012lld\n", z);
}
