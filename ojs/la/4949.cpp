#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 212345;

int c[N], v[N], p[N];
int n;
int memom[N][11];
int ze = 0, inf = INT_MAX;
inline int& M(int i, int k) {
	if(k < 0) return inf;
	if(i == n) return ze;
	return memom[i][k];
	//int &r = memo[i][k];
	//if(r != -1) return memo[i][k];
	//r = solve(i + 1, k);
	//r = max(r, min(v[p[i]] - c[p[i]], solve(i + 1, k - 1) - c[p[i]]));
	//return r;
}

int memo[N][12][13];
int solve(int i, int fst, int k) {
	if(k < 0) return INT_MAX;
	if(!k && fst) return v[p[fst - 1]] - c[p[fst - 1]];
	if(i == n) return 0;
	int &r = memo[i][fst][k];
	if(r != -1) return r;
	if(fst) r = solve(i + 1, fst, k);
	else r = solve(i + 1, i + 1, k);
	r = max(r, min(v[p[i]], solve(i + 1, fst, k - 1)) - c[p[i]]);
	return r;
}

void build2(int i, int fst, int k) {
	printf("build2(%d, %d, %d)\n", i, fst, k);
	if(!k && fst) { printf("choose %d\n", fst - 1); return; }
	if(i == n) return;
	int &r = memo[i][fst][k];
	if(fst && r == solve(i + 1, fst, k)) return build2(i + 1, fst, k);
	if(!fst && r == solve(i + 1, i + 1, k)) return build2(i + 1, i + 1, k);
	printf("choose %d\n", i);
	if(r == solve(i + 1, fst, k - 1) - c[p[i]]) return build2(i + 1, fst, k - 1);
}

int memo2[2000000][12];
int brut(int bm, int k) {
	int &r = memo2[bm][k];
	if(k < 0) return INT_MAX;
	if(r != -1) return r;
	if(bm == (1 << n) - 1) return r = 0;
	r = 0;
	for(int i = 0; i < n; i++)
		if(!((bm >> i) & 1))
			r = max(r, min(v[i] - c[i], brut(bm | (1 << i), k - 1) - c[i]));
	return r;
}

void build(int bm, int k) {
	printf("build(%d, %d)\n", bm, k);
	int &r = memo2[bm][k];
	if(r == 0) return;
	for(int i = 0; i < n; i++)
		if(!((bm >> i) & 1) && r == min(v[i], brut(bm | (1 << i), k - 1)) - c[i]) {
			printf("choose %d\n", i);
			if(r == brut(bm | (1 << i), k - 1) - c[i]) build(bm | (1 << i), k - 1);
			return;
		}
}

int main(int argn, char **args) {
	//srand(atoi(args[1]));
	int i, j, k, K;
	for_tests(tn, tt) {
		//memset(memo2, -1, sizeof memo2);
		scanf("%d %d", &n, &K);
		for(i = 0; i < n; i++) {
			scanf("%d %d", &v[i], &c[i]), p[i] = i;
			//p[i] = i; c[i] = rand() % 1000; v[i] = rand() % 2000;
			//printf("%d %d\n", v[i], c[i]);
		}
		sort(p, p + n, [](int i, int j) { return v[i] < v[j]; });
		for(i = n - 1; i >= 0; i--)
			for(k = 0; k <= K; k++)
				M(i, k) = max(M(i + 1, k), min(v[p[i]], M(i + 1, k - 1)) - c[p[i]]);
		printf("%d\n", M(0, K));
		//memset(memo, -1, sizeof memo);
		//printf("%d\n", solve(0, 0, K));
		//printf("%d BRUT\n", brut(0, K));
		//if(M(0, K) != brut(0, K)) build(0, K), build2(0, 0, K);
	}
}
