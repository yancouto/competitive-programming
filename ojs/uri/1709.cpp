#include <cstdio>
int p;
int nxt(int i) {
	if(i <= p / 2) return 2 * i;
	else return (i - (p/2)) * 2 - 1;
}
typedef unsigned long long ull;
int mdc(ull a, ull b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}
int mmc(ull a, ull b) {
	return (a / mdc(a, b)) * b;
}

bool seen[200009];
int main() {
	int i; ull tot = 1;
	scanf("%d", &p);
	for(i = 0; i < p; i++)
		if(!seen[i]) {
			int x = i, sz = 0;
			do {
				seen[x] = true;
				x = nxt(x); sz++;
			} while(x != i);
			tot = mmc(tot, sz);
		}
	printf("%llu\n", tot);
	return 0;	
}
