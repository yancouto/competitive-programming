#include <cstdio>
#include <cstring>
typedef unsigned long long ull;

int K[62];
int get(int i) {
<<<<<<< HEAD
	// printf("%d\n", i);
	if(K[i] == -1) K[i] = get(__builtin_popcount(i));
	return K[i];
}
ull l[2];
int k;
int memo[2][62][2][62];
int solve(int x, int d, bool prev, int num) {
	if(d == 61) return get(num) == k;
	// printf("%d %d %d %d\n", x, d, prev, num);
	int &m = memo[x][d][prev][num];
	// puts("AA");
	if(m != -1) return m;
	m = 0;
	for(int i = 0; i <= 1; i++) {
		if(prev && i && !(l[x] && (1ull << (60 - d))))
			break;
		m += solve(x, d + 1, prev && i == !!(l[x] && (1ull << (60 - d))), num + i);
=======
	if(K[i] == -1) K[i] = get(__builtin_popcount(i)) + 1;
	return K[i];
}

int k;
ull l[2];
ull memo[2][62][2][62];
ull solve(int x, int d, bool pref, int num) {
	if(d == 61) return (get(num) + 1) == k;
	ull &m = memo[x][d][pref][num];
	if(m != -1) return m;
	m = 0;
	for(int i = 0; i <= 1; i++) {
		if(pref && i && !(l[x] & (1ull << (60 - d))))
			break;
		if(d < 60 || num)
			m += solve(x, d + 1, pref && (i == !!(l[x] & (1ull << (60 - d)))), num + i);
		else
			m += (k == 0);
>>>>>>> ef070f1841ae0908392b2e41b764f4644af54046
	}
	return m;
}


int main() {
	memset(K, -1, sizeof K);
	K[0] = K[1] = 0;
	while(true) {
<<<<<<< HEAD
		scanf("%llu %llu %d", &l[0], &l[1], &k);
		l[1]--;
		if(l[0] == 0) return 0;
		memset(memo, -1, sizeof memo);
		printf("%d\n", ((l[1] <= 60)? get(l[1]) : solve(0, 0, true, 0)) - ((l[0] <= 60)? get(l[0]) : solve(1, 0, true, 0)));
=======
		scanf("%llu %llu %d", &l[0], &l[1], &k); l[0]--;
		if(!l[1]) return 0;
		memset(memo, -1, sizeof memo);
		printf("%llu\n", solve(1, 0, true, 0) - solve(0, 0, true, 0));
>>>>>>> ef070f1841ae0908392b2e41b764f4644af54046
	}
}