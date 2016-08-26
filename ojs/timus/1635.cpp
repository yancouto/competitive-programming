#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
ull hf[4009], hb[4009], pot[4009];
int n; char str[4009];

void pre() {
	int i;
	pot[0] = 1;
	for(i = 1; i <= n + 2; i++)
		pot[i] = mod(263ull * pot[i - 1]);
	for(i = 0; i < n; i++) {
		hf[i + 1] = mod(hf[i] + pot[i] * str[i]);
		hb[i + 1] = mod(hb[i] + pot[i] * str[n - 1 - i]);
	}
}

bool pal(int i, int j) {
	ull h1 = mod(hf[j + 1] - hf[i] + modn);
	ull h2 = mod(hb[n - i] - hb[n - 1 - j] + modn);
	if(i < n - 1 - j) h1 = mod(h1 * pot[n - 1 - j - i]);
	if(n - 1 - j < i) h2 = mod(h2 * pot[i - n + j + 1]);
	return h1 == h2;
}

int memo[4001][4001];
int solve(int i, int last) {
	if(!str[i]) return (last == i)? 0 : 10000000;
	int &r = memo[i][last];
	if(r != -1) return r;
	r = solve(i + 1, last);
	if(pal(last, i)) r = min(r, 1 + solve(i + 1, i + 1));
	return r;
}

void build(int i, int last) {
	if(!str[i]) return;
	putchar(str[i]);
	if(solve(i, last) == solve(i + 1, last)) build(i + 1, last);
	else { if(i != n - 1) putchar(' '); build(i + 1, i + 1); }
}

int main() {
	scanf("%s", str);
	n = strlen(str);
	pre();
	memset(memo, -1, sizeof memo);
	printf("%d\n", solve(0, 0));
	build(0, 0);
	putchar('\n');
}
